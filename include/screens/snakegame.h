#ifndef _SNAKEGAME_H
#define _SNAKEGAME_H

#include <interfaces/programScreen.h>
#include <models/pacman.h>
#include <models/axis.h>
#include <models/terrain.h>
#include <models/wall.h>
#include <models/cube.h>
#include <models/ghost.h>
#include <models/apple.h>
#include <utils/globalState.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <matrices.h>
#include <vector>
#include <utils/collisions.h>

class SnakeGame: public ProgramScreen {

    /* Guarda estado e informação sobre a tela de Jogo (camera, objetos) e os atualiza */

    public:
        SnakeGame();
        void updateScreenFrame() override;
    private:
        static const int n_obs = 5*15;

        std::unique_ptr<SceneObject> pacman;
        std::unique_ptr<SceneObject> axis;
        std::unique_ptr<SceneObject> terrain;
        std::unique_ptr<SceneObject> wall;
        std::unique_ptr<SceneObject> obsctacles[n_obs];
        std::unique_ptr<SceneObject> ghost_0;
        std::unique_ptr<SceneObject> ghost_1;
        std::unique_ptr<SceneObject> apple_0;
        std::unique_ptr<SceneObject> apple_1;
        glm::vec4 camera_pos_c         = glm::vec4(2.0f, 2.5f, 2.5f, 1.0f);
        glm::vec4 camera_front         = glm::vec4(0.0f, 0.0f,  0.0f, 0.0f);
        glm::vec4 camera_up_vector     = glm::vec4(0.0f, 1.0f,  0.0f, 0.0f);
        int game_mode = GameMode::Dev;
        bool should_switch_game = true;

        /* CAMERA LIVRE PARA MODO DEV */
        float g_camera_theta = - PI / 4; // Ângulo no plano ZX em relação ao eixo Z
        float g_camera_phi = - PI / 4;   // Ângulo em relação ao eixo Y
        glm::vec4 mov_direction_vector     = glm::vec4(0.0f, 0.0f,  0.0f, 0.0f);
        float delta_time = 0.0f;
        float last_frame = 0.0f;
        const float camera_speed = 2.5f;
        void updateFreeCamera();
        void updateMovDirVector();
        /* -------------------------- */

        /* CAMERA JOGO */
        void updateGameCamera();
        /* -------------------------- */

        float nearplane = -0.1f;
        float farplane  = -30.0f;
        float field_of_view = 3.141592 / 3.0f;

        void draw(std::unique_ptr<SceneObject> &object, glm::mat4 model, GLint model_uniform, GLint bbox_min_uniform, GLint bbox_max_uniform) override;
};

#endif
