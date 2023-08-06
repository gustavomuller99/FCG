
#include <models/terrain.h>
#include <utils/models.h>

GLuint Terrain::buildTriangles() {
    if(!this->vertex_array_object_id) {
        ObjModel planemodel("../../data/plane.obj");
        ComputeNormals(&planemodel);
        ObjectInfo object = BuildTrianglesAndAddToVirtualScene(&planemodel);
        this->vertex_array_object_id = object.vertex_array_object_id;
        this->renderingMode = object.rendering_mode;
        this->indexesNum = object.num_indices;
        this->firstIndex = object.first_index;
        this->bbox_min = object.bbox_min;
        this->bbox_max = object.bbox_max;
    }

    return this->vertex_array_object_id;
}

GLenum Terrain::getRenderingMode() {
    return this->renderingMode;
};

void* Terrain::getFirstIndex() {
    return (void*)(this->firstIndex * sizeof(GLuint));
}

GLuint Terrain::getIndexesNum() {
    return this->indexesNum;
}

float Terrain::getLineWidth() {
    return 10.0f;
}

glm::vec3 Terrain::getBBox_min() {
    return this->bbox_min;
}

glm::vec3 Terrain::getBBox_max() {
    return this->bbox_max;
}
