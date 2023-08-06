#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <interfaces/sceneObject.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils/utils.h>
#include <utils/models.h>
#include <glm/vec3.hpp>

class Terrain: public SceneObject {
    private:
        GLuint renderingMode;
        size_t firstIndex;
        GLuint indexesNum;
        GLuint vertex_array_object_id;
        glm::vec3 bbox_min;
        glm::vec3 bbox_max;
    public:
        GLuint buildTriangles() override;
        GLenum getRenderingMode() override;
        void* getFirstIndex() override;
        GLuint getIndexesNum() override;
        float getLineWidth() override;
        glm::vec3 getBBox_min() override;
        glm::vec3 getBBox_max() override;
};
#endif
