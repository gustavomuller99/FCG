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

        /* MOUSE INFO */
        double cursor_dx = 0.0f;
        double cursor_dy = 0.0f;
        /* ---------- */

        void setWPressed(bool pressed) {
            pressedKeys += (1 << KeyMapping::W) * (pressed ? 1 : -1);
        }
        bool getWPressed() {
            return pressedKeys & (1 << KeyMapping::W);
        }
        void setAPressed(bool pressed) {
            pressedKeys += (1 << KeyMapping::A) * (pressed ? 1 : -1);
        }
        bool getAPressed() {
            return pressedKeys & (1 << KeyMapping::A);
        }
        void setSPressed(bool pressed) {
            pressedKeys += (1 << KeyMapping::S) * (pressed ? 1 : -1);
        }
        bool getSPressed() {
            return pressedKeys & (1 << KeyMapping::S);
        }
        void setDPressed(bool pressed) {
            pressedKeys += (1 << KeyMapping::D) * (pressed ? 1 : -1);
        }
        bool getDPressed() {
            return pressedKeys & (1 << KeyMapping::D);
        }
        void setLeftMousePressed(bool pressed) {
            pressedKeys += (1 << KeyMapping::LeftMouse) * (pressed ? 1 : -1);
        }
        bool getLeftMousePressed() {
            return pressedKeys & (1 << KeyMapping::LeftMouse);
        }
        void setMPressed(bool pressed) {
            pressedKeys += (1 << KeyMapping::M) * (pressed ? 1 : -1);
        }
        bool getMPressed() {
            return pressedKeys & (1 << KeyMapping::M);
        }
};

extern GlobalState globalState;

#endif
