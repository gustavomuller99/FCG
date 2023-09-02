
#include <models/wall.h>
#include <utils/models.h>

GLuint Wall::buildTriangles() {
    if (vertex_array_object_id != -1)
        return vertex_array_object_id;

    ObjModel wallmodel("../../data/wall.obj");
    ComputeNormals(&wallmodel);
    ObjectInfo object = BuildTrianglesAndAddToVirtualScene(&wallmodel);
    this->vertex_array_object_id = object.vertex_array_object_id;
    this->renderingMode = object.rendering_mode;
    this->indexesNum = object.num_indices;
    this->firstIndex = object.first_index;
    this->bbox_min = object.bbox_min;
    this->bbox_max = object.bbox_max;

    return vertex_array_object_id;
}

GLenum Wall::getRenderingMode() {
    return this->renderingMode;
};

void* Wall::getFirstIndex() {
    return (void*)(this->firstIndex * sizeof(GLuint));
}

GLuint Wall::getIndexesNum() {
    return this->indexesNum;
}

float Wall::getLineWidth() {
    return 10.0f;
}

glm::vec3 Wall::getBBox_min() {
    return this->bbox_min;
}

glm::vec3 Wall::getBBox_max() {
    return this->bbox_max;
}

void Wall::setInitialPos(glm::vec4 initialPos) {
    this->pos = initialPos;
}

glm::vec4 Wall::getPos(){
    return this->pos;
}

void Wall::setSizeX(float newSize) {
    this->sizeX = newSize;
}

void Wall::setSizeZ(float newSize) {
    this->sizeZ = newSize;
}

float Wall::getSizeX() {
    return this->sizeX;
}

float Wall::getSizeZ() {
    return this->sizeZ;
}

