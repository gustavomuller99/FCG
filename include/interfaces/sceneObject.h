#ifndef _sceneObject_H
#define _sceneObject_H

#include <glad/glad.h>

class SceneObject {

    public:
        virtual void draw() = 0;

    private:
        virtual GLuint buildTriangles() = 0;
        
};

#endif