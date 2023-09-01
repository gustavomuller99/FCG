#include <cmath>
#include <memory>
#include <interfaces/sceneObject.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

bool CheckCubeCollision(std::unique_ptr<SceneObject> &one, std::unique_ptr<SceneObject> &two);
bool CheckSphereCubeCollision(std::unique_ptr<SceneObject> &one, std::unique_ptr<SceneObject> &two);
bool CheckSphereSphereCollision(std::unique_ptr<SceneObject> &pacman, std::unique_ptr<SceneObject> &item);
