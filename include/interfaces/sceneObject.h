#ifndef _sceneObject_H
#define _sceneObject_H

#include <glad/glad.h>

class SceneObject {

    public:
        virtual GLuint buildTriangles() = 0;
        virtual GLuint getRenderingMode() = 0;
        virtual void* getFirstIndex() = 0;
        virtual GLuint getIndexesNum() = 0;
        virtual float getLineWidth() {
            return 1.0f;
        };
    private:
};

#endif