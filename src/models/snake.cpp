#include <models/snake.h>

GLuint Snake::buildTriangles() {

    float model_coefficients[sections * section_points * 4];
    float color_coefficients[sections * section_points * 4];
    GLuint indices[(sections - 1) * (2 * section_points + 1)];
    float z = 0.f;

    for (GLuint i = 0; i < sections; i++) {
        float angle = 0.f;
        for (GLuint j = 0; j < section_points; j++) {
            float rad = angle * 2 * PI / 360;
            float ncos = cos(rad);
            float nsin = sin(rad);

            float x = radius * ncos;
            float y = radius * nsin;
            
            model_coefficients[i * section_points * 4 + j * 4] = x;
            model_coefficients[i * section_points * 4 + j * 4 + 1] = y;
            model_coefficients[i * section_points * 4 + j * 4 + 2] = z;
            model_coefficients[i * section_points * 4 + j * 4 + 3] = 1.0f;

            color_coefficients[i * section_points * 4 + j * 4] = 1.0f;
            color_coefficients[i * section_points * 4 + j * 4 + 1] = 0.0f;
            color_coefficients[i * section_points * 4 + j * 4 + 2] = 0.0f;
            color_coefficients[i * section_points * 4 + j * 4 + 3] = 1.0f;
        }
    }

    GLuint VBO_model_coefficients_id;
    glGenBuffers(1, &VBO_model_coefficients_id);
    GLuint vertex_array_object_id;
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

    // GL_TRIANGLE_STRIP
    for (GLuint i = 0; i < sections - 1; i++) {
        for (GLuint j = 0; j < 2 * section_points + 1; j += 2) {
            indices[i * section_points + j] = i * section_points + j;
            indices[i * section_points + j + 1] = i * (section_points + 1) + j;
        }
        indices[i * section_points + 2 * section_points + 1] = i * section_points;
    } 

    GLuint indices_id;
    glGenBuffers(1, &indices_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
    glBindVertexArray(0);

    return vertex_array_object_id;
};

GLenum Snake::getRenderingMode() {
    return GL_TRIANGLE_STRIP;
}

void* Snake::getFirstIndex() {
    return 0;
}

GLuint Snake::getIndexesNum() {
    return (sections - 1) * (2 * section_points + 1) + 1;
}

    
        
