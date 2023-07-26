#ifndef _HOME_H
#define _HOME_H

#include <interfaces/programScreen.h>

class Home: public ProgramScreen {

    /* Guarda estado e informação sobre a tela de Home (camera, objetos) e os atualiza */

    public:
        void updateScreenFrame() override;
    private:
        void draw(std::unique_ptr<SceneObject> &object, glm::mat4 model, GLint model_uniform) override;
};

#endif