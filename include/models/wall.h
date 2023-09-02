
#ifndef _WALL_h
#define _WALL_H
#include <interfaces/sceneObject.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils/utils.h>
#include <utils/models.h>
#include <glm/vec3.hpp>

class Wall: public SceneObject {
    private:
        GLuint renderingMode;
        size_t firstIndex;
        GLuint indexesNum;
        glm::vec3 bbox_min;
        glm::vec3 bbox_max;
        glm::vec4 pos;
        float sizeX;
        float sizeZ;
    public:
        GLuint buildTriangles() override;
        GLenum getRenderingMode() override;
        void* getFirstIndex() override;
        GLuint getIndexesNum() override;
        float getLineWidth() override;
        glm::vec3 getBBox_min() override;
        glm::vec3 getBBox_max() override;
        void setInitialPos(glm::vec4 initialPos) override;
        glm::vec4 getPos() override;
        float getSizeX() override;
        float getSizeZ() override;
        void setSizeX(float newValue) override;
        void setSizeZ(float newValue) override;
};
#endif
