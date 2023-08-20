#ifndef _sceneObject_H
#define _sceneObject_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


class SceneObject {

    public:
        virtual GLuint buildTriangles() = 0;
        virtual GLuint getRenderingMode() = 0;
        virtual void* getFirstIndex() = 0;
        virtual GLuint getIndexesNum() = 0;
        virtual void update() { };
        virtual void reset() { };
        virtual void setInitialPos(glm::vec4 initialPos) { };
        virtual float getLineWidth() {
            return 1.0f;
        };
        virtual glm::vec3 getBBox_min(){
            return glm::vec3(0.0f, 0.0f, 0.0f);
        };
        virtual glm::vec3 getBBox_max() {
            return glm::vec3(0.0f, 0.0f, 0.0f);
        };
        virtual glm::vec4 getPos() {
            return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        };
        virtual glm::vec4 getDir() {
            return glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        };
        ~SceneObject() = default;
    private:
};

#endif
