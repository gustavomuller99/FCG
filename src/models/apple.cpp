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
    int xOffset = abs(xMax - xMin);
    int zOffset = abs(zMin - zMax);

    float randomX = ((float)rand() / RAND_MAX) * (xMax - xMin) + xMin;
    float randomZ = ((float)rand() / RAND_MAX) * (zMax - zMin) + zMin;

    this->pos =  glm::vec4(randomX, this->pos.y, randomZ, 1.0f);
}
