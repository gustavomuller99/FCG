#ifndef _programScreen_H
#define _programScreen_H

#include <utils/matrices.h>
#include <interfaces/sceneObject.h>
#include <memory>

class ProgramScreen {
    public:
        virtual void updateScreenFrame() = 0;
    private:
        virtual void draw(std::unique_ptr<SceneObject> &object, glm::mat4 model, GLint model_uniform) = 0;

};

#endif