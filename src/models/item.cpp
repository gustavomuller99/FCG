#include <models/item.h>

GLuint Item::buildTriangles() {

    if (vertex_array_object_id != -1)
        return vertex_array_object_id;

    float model_coefficients[points * points * 4];
    float color_coefficients[points * points * 4];
    GLuint indices[2 * points * points];

    float phi = -M_PI / 2;
    for (int i = 0; i < points; i++, phi += angle_inc) {
        float theta = -M_PI;
        for (int j = 0; j < points; j++, theta += angle_inc) {
            float x = radius * sin(phi) * cos(theta);
            float y = radius * sin(phi) * sin(theta);
            float z = radius * cos(phi);

            model_coefficients[i * points * 4 + j * 4 + 0] = x;
            model_coefficients[i * points * 4 + j * 4 + 1] = y;
            model_coefficients[i * points * 4 + j * 4 + 2] = z;
            model_coefficients[i * points * 4 + j * 4 + 3] = 1.0;

            color_coefficients[i * points * 4 + j * 4 + 0] = 0.9;
            color_coefficients[i * points * 4 + j * 4 + 1] = 0.6;
            color_coefficients[i * points * 4 + j * 4 + 2] = 0.4;
            color_coefficients[i * points * 4 + j * 4 + 3] = 1.0;
        }
    }

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

    for (int i = 0; i < points - 1; i++) {
        for (int j = 0; j < points + 1; j++) {
            indices[i * 2 * (points + 1) + 2 * j] = i * points + (j % points);
            indices[i * 2 * (points + 1) + 2 * j + 1] = (i + 1) * points + (j % points);
        }
    }

    GLuint indices_id;
    glGenBuffers(1, &indices_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
    glBindVertexArray(0);

    return vertex_array_object_id;
};

GLenum Item::getRenderingMode() {
    return GL_TRIANGLE_STRIP;
}

void* Item::getFirstIndex() {
    return 0;
}

GLuint Item::getIndexesNum() {
    return 2 * points * points;
}


