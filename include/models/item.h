
#ifndef _ITEM_H
#define _ITEM_H

#include <interfaces/sceneObject.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils/utils.h>

class Item: public SceneObject {
    public:
        GLuint buildTriangles() override;
        GLenum getRenderingMode() override;
        void* getFirstIndex() override;
        GLuint getIndexesNum() override;
    private:
        GLfloat radius = 0.15;
        GLint points = 120;
        GLfloat angle_inc = (2 * M_PI * (360 / points)) / 360;
};

#endif
