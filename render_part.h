//
// Created by erik on 4/5/16.
//

#ifndef GAME_ENGINE_RENDER_PART_H
#define GAME_ENGINE_RENDER_PART_H


#include "material.h"
#include "mesh.h"

struct RenderPart {
    GLuint shaderId;
    Mesh mesh;
    Material material;
};

void renderPart(const RenderPart&);

#endif //GAME_ENGINE_RENDER_PART_H
