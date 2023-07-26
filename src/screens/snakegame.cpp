#include <screens/snakegame.h>

SnakeGame::SnakeGame() {
    snake = std::make_unique<Snake>(Snake());
    axis = std::make_unique<Axis>(Axis());
}

void SnakeGame::updateScreenFrame() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(globalState.g_GpuProgramID);

    GLint model_uniform           = glGetUniformLocation(globalState.g_GpuProgramID, "model");
    GLint view_uniform            = glGetUniformLocation(globalState.g_GpuProgramID, "view"); 
    GLint projection_uniform      = glGetUniformLocation(globalState.g_GpuProgramID, "projection"); 
    GLint render_as_black_uniform = glGetUniformLocation(globalState.g_GpuProgramID, "render_as_black"); 

    /* if modo dev */
    updateFreeCamera();
    /* else fixado na cobra */

    glm::vec4 camera_view_vector = camera_front;
    glm::mat4 projection = Matrix_Perspective(field_of_view, globalState.g_ScreenRatio, nearplane, farplane);
    glm::mat4 view = Matrix_Camera_View(camera_pos_c, camera_view_vector, camera_up_vector);

    glUniformMatrix4fv(view_uniform       , 1 , GL_FALSE , glm::value_ptr(view));
    glUniformMatrix4fv(projection_uniform , 1 , GL_FALSE , glm::value_ptr(projection));
    glUniform1i(render_as_black_uniform, false);

    draw(axis, Matrix_Identity(), model_uniform);
    //draw(snake, Matrix_Identity(), model_uniform);
}

void SnakeGame::draw(std::unique_ptr<SceneObject> &object, glm::mat4 model, GLint model_uniform) {
    GLuint vertex_array_object_id = object->buildTriangles();
    glBindVertexArray(vertex_array_object_id);
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
    glLineWidth(object->getLineWidth());
    glDrawElements(
        object->getRenderingMode(),
        object->getIndexesNum(),
        GL_UNSIGNED_INT,
        object->getFirstIndex()
    );
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