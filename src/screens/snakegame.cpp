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

    glm::vec4 camera_view_vector = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) - camera_pos_c; // olha para origem
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