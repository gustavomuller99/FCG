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
#define SNAKE  2
#define WALL 3
uniform int object_id;

uniform vec4 bbox_min;
uniform vec4 bbox_max;

uniform sampler2D TextureImage0; //TERRAIN
uniform sampler2D TextureImage1; //WALL TEXTURE

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

    if (object_id == TERRAIN || object_id == WALL) {
        U = texcoords.x;
        V = texcoords.y;
    }

    vec3 Kd0 = texture(TextureImage0, vec2(U,V)).rgb;
    vec3 Kd1 = texture(TextureImage1, vec2(U, V)).rgb;

    float lambert = max(0,dot(n,l));

    if( object_id == TERRAIN) {
        color.rgb = Kd0 * (lambert + 0.01);
    } else if(object_id == WALL) {
        color.rgb = Kd1 * (lambert + 0.01);
    } else {
        color.rgb = vec3(0.2, 0.2, 0.2);
    }

    color.a = 1;
    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
}

