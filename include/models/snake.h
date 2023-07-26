#ifndef _SNAKE_H
#define _SNAKE_H

#include <interfaces/sceneObject.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils/utils.h>

class Snake : public SceneObject {
    public:
        GLuint buildTriangles() override;
        GLenum getRenderingMode() override;
        void* getFirstIndex() override;
        GLuint getIndexesNum() override;

    private:
        GLuint section_points = 64;
        GLuint sections = 10;
        GLfloat section_spacing = 0.5f;
        GLfloat radius = 1.0f;
};

#endif