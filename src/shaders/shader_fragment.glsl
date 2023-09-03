#version 330 core

in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;
in vec3 vertex_color;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define TERRAIN 0
#define AXIS  1
#define PACMAN  2
#define WALL 3
#define CUBE 4
#define GHOST 5
#define APPLE 6

uniform int object_id;

uniform vec4 bbox_min;
uniform vec4 bbox_max;

uniform sampler2D Terrain;
uniform sampler2D Wall;
uniform sampler2D Pacman;
uniform sampler2D Ghost;
uniform sampler2D Apple;
uniform samplerCube Cube;

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

    // Vetor que define o sentido da reflexão especular ideal.
    vec4 r = -l + (2*n*dot(n, l));

    vec4 h = normalize(v + l);

    // Espectro da fonte de iluminação
    vec3 I = vec3(1.0,1.0,1.0); // PREENCH AQUI o espectro da fonte de luz
    // Espectro da luz ambiente
    vec3 Ia = vec3(0.2,0.2,0.2); // PREENCHA AQUI o espectro da luz ambiente

    vec3 lambert = I*max(0, dot(n, l)); // PREENCHA AQUI o termo difuso de Lambert

    vec3 ambient_term = vec3(0, 0, 0);
    vec3 phong_specular_term = vec3(0, 0, 0);
    float q = 5;

    vec3 Kd0 = vec3(0.2, 0.2, 0.2);

    vec3 Ka = vec3(0,0,0);
    vec3 Ks = vec3(0,0,0);

    float U = 0.0;
    float V = 0.0;

    switch(object_id) {
        case AXIS:
            color.rgb = vec3(1.0, 1.0, 1.0);
            break;

        case TERRAIN:
            U = texcoords.x;
            V = texcoords.y;
            Kd0 = texture(Terrain, vec2(U,V)).rgb;

            color.rgb = Kd0 * (lambert + 0.01 + ambient_term + phong_specular_term);
            color.a = 1;
            color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
            break;

        case WALL:
            U = texcoords.x;
            V = texcoords.y;
            Kd0 = texture(Wall, vec2(U,V)).rgb;

            color.rgb = Kd0 * (lambert + 0.01 + ambient_term + phong_specular_term);
            color.a = 1;
            color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
            break;

        case GHOST:
            U = texcoords.x;
            V = texcoords.y;
            Kd0 = texture(Ghost, vec2(U,V)).rgb;

            Ka = vec3(0.4, 0.2, 0.2);
            Ks = vec3(1, 1, 1);
            q = 128;
            // Termo ambiente
            ambient_term = Ka*Ia;
            // Termo especular utilizando o modelo de iluminação de Phong
            phong_specular_term = Ks*I*max((pow(dot(n, h), q)), 0);

            color.rgb = Kd0 * (lambert + 0.01 + ambient_term + phong_specular_term);
            color.a = 1;
            color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
            break;

        case APPLE:
            U = texcoords.x;
            V = texcoords.y;
            Kd0 = texture(Apple, vec2(U,V)).rgb;

            Ka = vec3(1, 1, 1);
            Ks = vec3(1, 1, 1);
            q = 128;
            // Termo ambiente
            ambient_term = Ka*Ia;
            // Termo especular utilizando o modelo de iluminação de Phong
            phong_specular_term = Ks*I*max((pow(dot(n, h), q)), 0);

            color.rgb = Kd0 * (lambert + 0.01 + ambient_term + phong_specular_term);
            color.a = 1;
            color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
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

            Ka = vec3(1, 1, 1);
            Ks = vec3(1, 1, 1);
            q = 128;
            // Termo ambiente
            ambient_term = Ka*Ia;
            // Termo especular utilizando o modelo de iluminação de Phong
            phong_specular_term = Ks*I*max((pow(dot(n, h), q)), 0);

            color.rgb = Kd0 * (lambert + 0.01 + ambient_term + phong_specular_term);
            color.a = 1;
            color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
            break;

        case CUBE:
            Kd0 = texture(Cube, vec3(position_model[0], position_model[1], position_model[2])).rgb;
            /*color.rgb = Kd0 * (lambert + 0.01 + ambient_term + phong_specular_term);
            color.a = 1;
            color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);*/

            color.rgb = Kd0 * vertex_color;
            break;

        default:
            break;
    }
}

