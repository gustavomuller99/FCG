#include <utils/collisions.h>

//FONTE https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection#:~:text=If%20both%20the%20horizontal%20and%20vertical%20edges%20overlap%20we%20have%20a%20collision.&text=We%20check%20if%20the%20right,similarly%20for%20the%20vertical%20axis.
//Pacman - Ghost
bool CheckCubeCollision(std::unique_ptr<SceneObject> &one, std::unique_ptr<SceneObject> &two) // AABB - AABB collision
{
    // collision x-axis?
    bool collisionX = one->getPos().x + one->getSize() >= two->getPos().x &&
        two->getPos().x + two->getSize() >= one->getPos().x;
    // collision y-axis?
    bool collisionY = one->getPos().y + one->getSize() >= two->getPos().y &&
        two->getPos().y + two->getSize() >= one->getPos().y;

    bool collisionZ = one->getPos().z + one->getSize() >= two->getPos().z && two->getPos().z + two->getSize() >= one->getPos().z;
    // collision only if on both axes
    return collisionX && collisionY && collisionZ;
}

//Pacman - Obstacles
bool CheckSphereCubeCollision(std::unique_ptr<SceneObject> &one, std::unique_ptr<SceneObject> &two) // AABB - Circle collision
{
    // get center point circle first
    glm::vec4 center(one->getPos());
    center.y = 0.0f;
    // calculate AABB info (center)
    glm::vec4 aabb_center(
        two->getPos().x ,
        0.0f,
        two->getPos().z,
        0.0f
    );
    // get difference vector between both centers
    glm::vec4 difference = center - aabb_center;
    glm::vec4 clamped = glm::clamp(difference, -two->getSize(), two->getSize());
    // add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec4 closest = aabb_center + clamped;
    // retrieve vector between center circle and closest point AABB and check if length <= size
    difference = closest - center;
    return glm::length(difference) < one->getSize();
}

//Pacman - Items
bool CheckSphereSphereCollision(std::unique_ptr<SceneObject> &pacman, std::unique_ptr<SceneObject> &item) { //Circle - Circle Collision
    // get center point circle first
    glm::vec4 centerPacman = pacman->getPos();
    // calculate AABB info (center)
    glm::vec4 centerItem = item->getPos();
    // get difference vector between both centers
    glm::vec4 difference = centerPacman - centerItem;
    glm::vec4 clamped = glm::clamp(difference, -item->getSize(), item->getSize());
    // add clamped value to itemcenter and we get the value of circle1 closest to circle0
    glm::vec4 closest = centerItem + clamped;
    // retrieve vector between center circle and closest point AABB and check if length <= size
    difference = closest - centerPacman;
    return glm::length(difference) < pacman->getSize();
}




