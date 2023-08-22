#include <models/cube.h>

GLuint Cube::buildTriangles() {

    if (vertex_array_object_id != -1)
        return vertex_array_object_id;

    float model_coefficients[8 * 4] = {
        -radius, 2 * radius,  radius, 1.0f,
        -radius, 0.0f,  radius, 1.0f,
         radius, 0.0f,  radius, 1.0f,
         radius, 2 * radius,  radius, 1.0f,
        -radius, 2 * radius, -radius, 1.0f,
        -radius, 0.0f, -radius, 1.0f,
         radius, 0.0f, -radius, 1.0f,
         radius, 2 * radius, -radius, 1.0f,
    };

    float color_coefficients[8 * 4] = {
        0.3, 0.32, 0.72, 1.0,
        0.3, 0.32, 0.72, 1.0,
        0.3, 0.32, 0.72, 1.0,
        0.3, 0.32, 0.72, 1.0,
        0.3, 0.32, 0.72, 1.0,
        0.3, 0.32, 0.72, 1.0,
        0.3, 0.32, 0.72, 1.0,
        0.3, 0.32, 0.72, 1.0,
    };

    GLuint VBO_model_coefficients_id;
    glGenBuffers(1, &VBO_model_coefficients_id);
    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_model_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(model_coefficients), model_coefficients);
    GLuint location = 0; // "(location = 0)" em "shader_vertex.glsl"
    GLint  number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint VBO_color_coefficients_id;
    glGenBuffers(1, &VBO_color_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(color_coefficients), color_coefficients);
    location = 1; // "(location = 1)" em "shader_vertex.glsl"
    number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint indices[6 * 2 * 3] = {
        0, 1, 2,
        7, 6, 5,
        3, 2, 6,
        4, 0, 3,
        4, 5, 1,
        1, 5, 6,
        0, 2, 3,
        7, 5, 4,
        3, 6, 7,
        4, 3, 7,
        4, 1, 0,
        1, 6, 2,
    };

    GLuint indices_id;
    glGenBuffers(1, &indices_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
    glBindVertexArray(0);

    return vertex_array_object_id;
}

GLenum Cube::getRenderingMode() {
    return GL_TRIANGLES;
};

void* Cube::getFirstIndex() {
    return 0;
}

GLuint Cube::getIndexesNum() {
    return 6 * 2 * 3;
}

float Cube::getLineWidth() {
    return 10.0f;
}
