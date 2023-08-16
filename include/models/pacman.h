#ifndef _SNAKE_H
#define _SNAKE_H

#include <interfaces/sceneObject.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils/utils.h>

class Pacman : public SceneObject {
    public:
        GLuint buildTriangles() override;
        GLenum getRenderingMode() override;
        void* getFirstIndex() override;
        GLuint getIndexesNum() override;
        glm::vec3 getPos() override;

    private:
        GLfloat radius = 0.25;
        GLint points = 120;
        GLfloat angleInc = (2 * M_PI * (360 / points)) / 360;

        glm::vec4 dir = glm::vec4(1.0, 0.0, 0.0, 0.0);
        glm::vec4 pos = glm::vec4(0.0, radius, 0.0, 0.0);
};

#endif
