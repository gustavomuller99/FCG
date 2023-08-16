#ifndef _SNAKE_H
#define _SNAKE_H

#include <interfaces/sceneObject.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <utils/globalState.h>
#include <glm/gtc/type_ptr.hpp>
#include <utils/utils.h>

class Pacman : public SceneObject {
    public:
        GLuint buildTriangles() override;
        GLenum getRenderingMode() override;
        void* getFirstIndex() override;
        GLuint getIndexesNum() override;
        glm::vec4 getPos() override;
        glm::vec4 getDir() override;
        void update() override;
        void reset() override;

    private:
        GLfloat radius = 0.25;
        GLint points = 120;
        GLfloat angle_inc = (2 * M_PI * (360 / points)) / 360;

        GLfloat speed = 1.0f;
        GLfloat tilt = 0.02;
        GLfloat pos_theta = 0.0f;
        float last_frame = 0.0f;
        glm::vec4 dir = glm::vec4(1.0, 0.0, 0.0, 0.0);
        glm::vec4 pos = glm::vec4(0.0, radius, 0.0, 1.0);
};

#endif
