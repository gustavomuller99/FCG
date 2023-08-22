#ifndef _GHOST_H
#define _GHOST_H

#include <interfaces/sceneObject.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <utils/globalState.h>
#include <glm/gtc/type_ptr.hpp>
#include <utils/utils.h>

class Ghost : public SceneObject {
     private:
        GLuint renderingMode;
        size_t firstIndex;
        GLuint indexesNum;
        glm::vec3 bbox_min;
        glm::vec3 bbox_max;
        glm::vec4 pos;
        float last_frame = 0.0f;
        bool bChangeDirection = false;
    public:
        GLuint buildTriangles() override;
        GLenum getRenderingMode() override;
        void* getFirstIndex() override;
        GLuint getIndexesNum() override;
        float getLineWidth() override;
        glm::vec3 getBBox_min() override;
        glm::vec3 getBBox_max() override;
        glm::vec4 getPos() override;
        void update() override;
        void setInitialPos(glm::vec4 initialPos) override;
};

#endif
