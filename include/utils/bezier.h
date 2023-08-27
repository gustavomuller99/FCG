
#ifndef _BEZIER_H
#define _BEZIER_H

#include <tiny_obj_loader.h>
#include <utils/matrices.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float getPt(float n1 , float n2 , float perc);
glm::vec2 getNextPt(float t, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4);

#endif
