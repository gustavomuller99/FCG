#include <models/apple.h>
#include <utils/models.h>

GLuint Apple::buildTriangles() {

    if (vertex_array_object_id != -1)
        return vertex_array_object_id;

    ObjModel applemodel("../../data/apple.obj");
    ComputeNormals(&applemodel);
    ObjectInfo object = BuildTrianglesAndAddToVirtualScene(&applemodel);
    this->vertex_array_object_id = object.vertex_array_object_id;
    this->renderingMode = object.rendering_mode;
    this->indexesNum = object.num_indices;
    this->firstIndex = object.first_index;
    this->bbox_min = object.bbox_min;
    this->bbox_max = object.bbox_max;


    return vertex_array_object_id;
}

void Apple::update() {
    float current_frame = glfwGetTime();
    float delta_time = current_frame - this->last_frame;
    this->last_frame = current_frame;
    float speed = delta_time * 1.0;

    glm::vec2 nextPt = getNextPt(this->t, this->p1, this->p2, this->p3, this->p4);
    this->pos.z += nextPt.x;

    if(!this->bChangeDirection) {
        if(this->t >= 0.5) {
            this->pos.y = this->pos.y + nextPt.y >= 1 ? 1 : this->pos.y + nextPt.y;
        } else {
            this->pos.y = this->pos.y - nextPt.y <= 0.5 ? 0.5 : this->pos.y - nextPt.y;
        }
        this->t = this->t + speed >= 1 ? 1 : this->t + speed;

        if(this->t >= 1) {
            this->bChangeDirection = true;
        }
        return;
    }

    if(this->t <= 0.5) {
        this->pos.y = this->pos.y + nextPt.y >= 1 ? 1 : this->pos.y + nextPt.y;
    } else {-
        this->pos.y = this->pos.y - nextPt.y <= 0.5 ? 0.5 : this->pos.y - nextPt.y;
    }

    this->t = this->t - speed <= 0 ? 0 : this->t - speed;

    if(this->t <= 0) {
        this->bChangeDirection = false;
    }
}

void Apple::setInitialPos(glm::vec4 initialPos) {
    this->pos = initialPos;
}

GLenum Apple::getRenderingMode() {
    return this->renderingMode;
};

void* Apple::getFirstIndex() {
    return (void*)(this->firstIndex * sizeof(GLuint));
}

GLuint Apple::getIndexesNum() {
    return this->indexesNum;
}

glm::vec4 Apple::getPos() {
    return this->pos;
}

void Apple::getNewPosition(int xMin, int xMax, int zMin, int zMax) {

    float randomX = ((float)rand() / RAND_MAX) * (xMax - xMin) + xMin;
    float randomZ = ((float)rand() / RAND_MAX) * (zMax - zMin) + zMin;

    this->pos =  glm::vec4(randomX, this->pos.y, randomZ, 1.0f);
}

float Apple::getSize(){
    return 0.3f;
}
