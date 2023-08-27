#ifndef _APPLE_H
#define _APPLE_H

#include <interfaces/sceneObject.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <utils/globalState.h>
#include <glm/gtc/type_ptr.hpp>
#include <utils/utils.h>

class Apple : public SceneObject {
    public:
        GLuint buildTriangles() override;
        GLenum getRenderingMode() override;
        void* getFirstIndex() override;
        GLuint getIndexesNum() override;
        glm::vec4 getPos() override;
        void getNewPosition(int xMin, int xMax, int zMin, int zMax) override;
        void setInitialPos(glm::vec4 initialPos) override;
        //void update() override;

    private:
        glm::vec4 pos = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        GLuint renderingMode;
        size_t firstIndex;
        GLuint indexesNum;
        glm::vec3 bbox_min;
        glm::vec3 bbox_max;
        float last_frame = 0.0f;
};

#endif
