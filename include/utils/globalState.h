#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <glad/glad.h>
#include <utils/utils.h>
#include <memory>

class GlobalState {
    public:
        GLuint g_GpuProgramID = 0;
        GLuint64 pressedKeys = 0;
        float g_ScreenRatio = 1.0f;

        void setWPressed(bool pressed) {
            pressedKeys += (1 << KeyMapping::W);
        }

        bool getWPressed() {
            return pressedKeys & (1 << KeyMapping::W);
        } 
};

extern GlobalState globalState;

#endif