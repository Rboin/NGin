//
// Created by Erik on 3/21/2016.
//

#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H

#include "engine.h"

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float power;
};

void drawMaterial(const Material&, const GLuint);

#endif //GAME_ENGINE_MATERIAL_H
