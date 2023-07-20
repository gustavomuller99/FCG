#include <interfaces/sceneObject.h>

class Snake : public SceneObject {
    public:
        void draw() override {

        }

    private:
        GLuint buildTriangles() override {
            return 0;
        }

};