#ifndef _CUBE_H
#define _CUBE_H

#include <interfaces/sceneObject.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils/utils.h>

class Cube: public SceneObject {
    public:
        GLuint buildTriangles() override;
        GLenum getRenderingMode() override;
        void* getFirstIndex() override;
        GLuint getIndexesNum() override;
        float getLineWidth() override;
        glm::vec4 getPos() override;
        float getSize() override;
        void setInitialPos(glm::vec4 initialPos) override;
        float getSizeX() override;
        float getSizeZ() override;

    private:
        GLfloat radius = 0.3;
        glm::vec4 pos;
};

#endif
