#ifndef _SKYBOX_H
#define _SKYBOX_H

#include <interfaces/sceneObject.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils/utils.h>
#include <models/skybox.h>

class Skybox: public SceneObject {
    public:
        GLuint buildTriangles() override;
        GLenum getRenderingMode() override;
        void* getFirstIndex() override;
        GLuint getIndexesNum() override;

    private:
        GLfloat radius = 1;
        glm::vec4 pos;
};

#endif
