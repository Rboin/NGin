//
// Created by erik on 4/5/16.
//

#include "render_part.h"

void renderPart(const RenderPart &part) {
    useMaterial(part.material, part.shaderId);
    drawMesh(part.mesh);
}
