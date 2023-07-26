#ifndef _SNAKEGAME_H
#define _SNAKEGAME_H

#include <interfaces/programScreen.h>
#include <models/snake.h>
#include <models/axis.h>
#include <utils/globalState.h>

class SnakeGame: public ProgramScreen {

    /* Guarda estado e informação sobre a tela de Jogo (camera, objetos) e os atualiza */

    public:
        SnakeGame();
        void updateScreenFrame() override;
    private:
        std::unique_ptr<SceneObject> snake;
        std::unique_ptr<SceneObject> axis;
        glm::vec4 camera_pos_c         = glm::vec4(2.0f, 2.5f, 2.5f, 1.0f);
        glm::vec4 camera_up_vector     = glm::vec4(0.0f, 1.0f,  0.0f, 0.0f);
        float nearplane = -0.1f;
        float farplane  = -10.0f;
        float field_of_view = 3.141592 / 3.0f;

        void draw(std::unique_ptr<SceneObject> &object, glm::mat4 model, GLint model_uniform) override;
};

#endif