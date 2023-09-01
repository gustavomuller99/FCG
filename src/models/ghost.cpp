#include <models/ghost.h>
#include <utils/models.h>

#define MAP_SIZE 10

GLuint Ghost::buildTriangles() {

    if (vertex_array_object_id != -1)
        return vertex_array_object_id;

    ObjModel ghosttmodel("../../data/ghost.obj");
    ComputeNormals(&ghosttmodel);
    ObjectInfo object = BuildTrianglesAndAddToVirtualScene(&ghosttmodel);
    this->vertex_array_object_id = object.vertex_array_object_id;
    this->renderingMode = object.rendering_mode;
    this->indexesNum = object.num_indices;
    this->firstIndex = object.first_index;
    this->bbox_min = object.bbox_min;
    this->bbox_max = object.bbox_max;


    return vertex_array_object_id;
}

void Ghost::setInitialPos(glm::vec4 initialPos) {
    this->pos = initialPos;
}

void Ghost::update() {
    float current_frame = glfwGetTime();
    float delta_time = current_frame - last_frame;
    last_frame = current_frame;
    float cur_speed = speed * delta_time;

    if(!this->bChangeDirection) {
        this->pos.x += cur_speed;
        if(this->pos.x >= MAP_SIZE - 1.5) {
            this->bChangeDirection = true;
        }
    } else {
        this->pos.x -= cur_speed;
        if(this->pos.x <= -MAP_SIZE + 2) {
            this->bChangeDirection = false;
        }
    }
}

glm::vec4 Ghost::getPos() {
    return this->pos;
}

GLenum Ghost::getRenderingMode() {
    return this->renderingMode;
};

void* Ghost::getFirstIndex() {
    return (void*)(this->firstIndex * sizeof(GLuint));
}

GLuint Ghost::getIndexesNum() {
    return this->indexesNum;
}

float Ghost::getLineWidth() {
    return 10.0f;
}

glm::vec3 Ghost::getBBox_min() {
    return this->bbox_min;
}

glm::vec3 Ghost::getBBox_max() {
    return this->bbox_max;
}

float Ghost::getSize() {
    return 0.80;
}
