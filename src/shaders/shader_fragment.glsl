#version 330 core

in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define TERRAIN 0
#define AXIS  1
#define PACMAN  2
#define WALL 3
#define CUBE 4
uniform int object_id;

uniform vec4 bbox_min;
uniform vec4 bbox_max;

uniform sampler2D Terrain;
uniform sampler2D Wall;
uniform sampler2D Pacman;

out vec4 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

void main()
{
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    vec4 p = position_world;

    vec4 n = normalize(normal);

    vec4 l = normalize(vec4(1.0,1.0,0.0,0.0));

    vec4 v = normalize(camera_position - p);

    float U = 0.0;
    float V = 0.0;

    vec3 Kd0 = vec3(0.2, 0.2, 0.2);

    switch(object_id) {
        case TERRAIN:
            U = texcoords.x;
            V = texcoords.y;
            Kd0 = texture(Terrain, vec2(U,V)).rgb;
            break;
        case WALL:
            U = texcoords.x;
            V = texcoords.y;
            Kd0 = texture(Wall, vec2(U,V)).rgb;
            break;
        case PACMAN:
            vec4 bbox_center = (bbox_min + bbox_max) / 2.0;

            float r = 1.0;
            vec4 p_texture =
                bbox_center +
                r * normalize(position_model - bbox_center);
            vec4 p_c = p_texture - bbox_center;

            float theta = atan(p_c[0], p_c[2]);
            float phi = asin(p_c[1] / r);

            U = (theta + M_PI) / (2 * M_PI);
            V = (phi + M_PI / 2) / M_PI;
            Kd0 = texture(Pacman, vec2(U,V)).rgb + vec3(.8f, .8f, 0.0f);
            break;
        case CUBE:
        default:
            break;
    }

    float lambert = max(0,dot(n,l));
    color.rgb = Kd0 * (lambert + 0.01);

    color.a = 1;
    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
}

