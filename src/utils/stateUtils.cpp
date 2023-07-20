#include <glad/glad.h>

#include "../screens/home.cpp"
#include "../screens/snakegame.cpp"
#include <utils.h>

class GlobalState {
    public:
        ProgramScreen currentScreen = Home();
        GLuint64 pressedKeys = 0;

        void setWPressed(bool pressed) {
            pressedKeys += (1 << KeyMapping::W);
        }

        bool getWPressed() {
            return pressedKeys & (1 << KeyMapping::W);
        } 
};