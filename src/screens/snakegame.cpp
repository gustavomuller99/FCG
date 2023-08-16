#include <screens/snakegame.h>
#include <matrices.h>
#include <math.h>

#define TERRAIN 0
#define AXIS  1
#define SNAKE  2
#define WALL 3

#define MAP_SIZE 10

SnakeGame::SnakeGame() {
    pacman = std::make_unique<Pacman>(Pacman());
    axis = std::make_unique<Axis>(Axis());
    terrain = std::make_unique<Terrain>(Terrain());
    wall = std::make_unique<Wall>(Wall());
}

void SnakeGame::updateScreenFrame() {
    glClearColor(0.65f, 0.92f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(globalState.g_GpuProgramID);

    GLint model_uniform           = glGetUniformLocation(globalState.g_GpuProgramID, "model");
    GLint view_uniform            = glGetUniformLocation(globalState.g_GpuProgramID, "view");
    GLint projection_uniform      = glGetUniformLocation(globalState.g_GpuProgramID, "projection");
    GLint object_id               = glGetUniformLocation(globalState.g_GpuProgramID, "object_id");
    GLint render_as_black_uniform = glGetUniformLocation(globalState.g_GpuProgramID, "render_as_black");
    GLint bbox_min_uniform        = glGetUniformLocation(globalState.g_GpuProgramID, "bbox_min");
    GLint bbox_max_uniform        = glGetUniformLocation(globalState.g_GpuProgramID, "bbox_max");

    if (globalState.getMPressed() && should_switch_game) {
        should_switch_game = false;
        switch (game_mode) {
            case GameMode::Dev:
                game_mode = GameMode::Running;
                break;
            default:
                game_mode = GameMode::Dev;
                break;
        }
    } else if (!globalState.getMPressed()) {
        should_switch_game = true;
    }

    if (game_mode == GameMode::Dev) {
        /* reset all in game elements */
        pacman->reset();

        updateFreeCamera();
    } else {
        /* update all in game elements */
        pacman->update();
        /* reward[i]->update() */

        /* check for collisions */

        updateGameCamera();
    }

    glm::vec4 camera_view_vector = camera_front;
    glm::mat4 projection = Matrix_Perspective(field_of_view, globalState.g_ScreenRatio, nearplane, farplane);
    glm::mat4 view = Matrix_Camera_View(camera_pos_c, camera_view_vector, camera_up_vector);

    glUniformMatrix4fv(view_uniform       , 1 , GL_FALSE , glm::value_ptr(view));
    glUniformMatrix4fv(projection_uniform , 1 , GL_FALSE , glm::value_ptr(projection));

    glUniform1i(object_id, TERRAIN);
    draw(terrain,  Matrix_Identity() * Matrix_Scale(MAP_SIZE, 1.0f, MAP_SIZE), model_uniform, bbox_min_uniform, bbox_max_uniform);

    glUniform1i(object_id, WALL);

    //LADO 1
    draw(wall,
         Matrix_Translate(MAP_SIZE, 0.0f, MAP_SIZE/1.65) * Matrix_Scale(0.5f, 0.5f, 0.6f),
         model_uniform,
         bbox_min_uniform,
         bbox_max_uniform);
    draw(wall,
         Matrix_Translate(MAP_SIZE, 0.0f, -MAP_SIZE/2.45) * Matrix_Scale(0.5f, 0.5f, 0.6f),
         model_uniform,
         bbox_min_uniform,
         bbox_max_uniform);

    //LADO 2
    draw(wall,
         Matrix_Identity() * Matrix_Translate(-MAP_SIZE, 0.0f, MAP_SIZE/1.65) * Matrix_Scale(0.5f, 0.5f, 0.6f),
         model_uniform,
         bbox_min_uniform, bbox_max_uniform);
    draw(wall,
         Matrix_Identity() * Matrix_Translate(-MAP_SIZE, 0.0f, -MAP_SIZE/2.45) * Matrix_Scale(0.5f, 0.5f, 0.6f),
         model_uniform,
         bbox_min_uniform,
         bbox_max_uniform);

    //LADO 3
    draw(wall,
         Matrix_Identity() * Matrix_Rotate_Y(M_PI/2) * Matrix_Translate(MAP_SIZE, 0.0f, MAP_SIZE/1.65) * Matrix_Scale(0.5f, 0.5f, 0.6f),
         model_uniform,
         bbox_min_uniform,
         bbox_max_uniform);
    draw(wall,
         Matrix_Identity() * Matrix_Rotate_Y(M_PI/2) * Matrix_Translate(MAP_SIZE, 0.0f, -MAP_SIZE/2.45) * Matrix_Scale(0.5f, 0.5f, 0.6f),
         model_uniform,
         bbox_min_uniform,
         bbox_max_uniform);

    //LADO 4
    draw(wall,
         Matrix_Identity() * Matrix_Rotate_Y(M_PI/2) * Matrix_Translate(-MAP_SIZE, 0.0f, MAP_SIZE/1.65) * Matrix_Scale(0.5f, 0.5f, 0.6f),
         model_uniform,
         bbox_min_uniform,
         bbox_max_uniform);
    draw(wall,
         Matrix_Identity() * Matrix_Rotate_Y(M_PI/2) * Matrix_Translate(-MAP_SIZE, 0.0f, -MAP_SIZE/2.45) * Matrix_Scale(0.5f, 0.5f, 0.6f),
         model_uniform,
         bbox_min_uniform,
         bbox_max_uniform);

    glUniform1i(object_id, AXIS);
    draw(axis, Matrix_Identity(), model_uniform, bbox_min_uniform, bbox_max_uniform);

    draw(pacman, Matrix_Translate(pacman->getPos()[0], pacman->getPos()[1], pacman->getPos()[2]), model_uniform, bbox_min_uniform, bbox_max_uniform);
}

void SnakeGame::draw(std::unique_ptr<SceneObject> &object, glm::mat4 model, GLint model_uniform, GLint bbox_min_uniform, GLint bbox_max_uniform) {
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));

    GLuint vertex_array_object_id = object->buildTriangles();
    glBindVertexArray(vertex_array_object_id);

    glm::vec3 bbox_min = object->getBBox_min();
    glm::vec3 bbox_max = object->getBBox_max();
    glUniform4f(bbox_min_uniform, bbox_min.x, bbox_min.y, bbox_min.z, 1.0f);
    glUniform4f(bbox_max_uniform, bbox_max.x, bbox_max.y, bbox_max.z, 1.0f);

    glLineWidth(object->getLineWidth());
    glDrawElements(
        object->getRenderingMode(),
        object->getIndexesNum(),
        GL_UNSIGNED_INT,
        object->getFirstIndex()
    );

    glBindVertexArray(0);
}

void SnakeGame::updateFreeCamera() {

    if (globalState.getLeftMousePressed()) {
        g_camera_theta += 0.02f * globalState.cursor_dx;
        g_camera_phi   -= 0.02f * globalState.cursor_dy;

        float phimax = 3.141592f/2;
        float phimin = -phimax;

        if (g_camera_phi > phimax)
            g_camera_phi = phimax;

        if (g_camera_phi < phimin)
            g_camera_phi = phimin;

        globalState.cursor_dx = 0.0f;
        globalState.cursor_dy = 0.0f;
    }

    float y = sin(g_camera_phi);
    float z = cos(g_camera_phi)*cos(g_camera_theta);
    float x = cos(g_camera_phi)*sin(g_camera_theta);
    camera_front = glm::vec4(x, y, -z, 0.0f);

    float current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
    float cur_speed = camera_speed * delta_time;

    if (globalState.getWPressed() ||
        globalState.getAPressed() ||
        globalState.getSPressed() ||
        globalState.getDPressed()) {

        updateMovDirVector();
        camera_pos_c += mov_direction_vector * cur_speed;
    }
}

void SnakeGame::updateMovDirVector() {
    mov_direction_vector = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    if (globalState.getWPressed()) {
        mov_direction_vector += camera_front;
    }

    if (globalState.getSPressed()) {
        mov_direction_vector += -camera_front;
    }

    if (globalState.getAPressed()) {
        glm::vec4 dir = crossproduct(camera_front, camera_up_vector);
        mov_direction_vector += -(dir / norm(dir));
    }

    if (globalState.getDPressed()) {
        glm::vec4 dir = crossproduct(camera_front, camera_up_vector);
        mov_direction_vector += (dir / norm(dir));
    }
}

void SnakeGame::updateGameCamera() {
    camera_front = pacman->getDir();
    camera_front[1] = - M_PI / 4;

    camera_pos_c = pacman->getPos() - pacman->getDir() - pacman->getDir();
    camera_pos_c[1] = 1.75f;
}
