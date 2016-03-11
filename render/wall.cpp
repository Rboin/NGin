//
// Created by erik on 3/11/16.
//

#include "render.h"

void render_wall(vec3 pos, vec3 look, vec3 scale) {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    if (look.x)
        glRotatef(look.x, 1, 0, 0);
    if (look.y)
        glRotatef(look.y, 0, 1, 0);
    if (look.z)
        glRotatef(look.z, 0, 0, 1);

    glColor3f(.23921f, .6f, .69019f);

    vec3 incr = scale / 2.0f;

    // front
    glPushMatrix();
    glTranslatef(-incr.x,incr.y,-incr.z);
    glRectf(0, 0, scale.x, -scale.y);
    glPopMatrix();

    // back
    glPushMatrix();
    glTranslatef(-incr.x,incr.y,incr.z);
    glRectf(0, 0, scale.x, -scale.y);
    glPopMatrix();

    // left side
    glPushMatrix();
    glTranslatef(-incr.x,incr.y,incr.z);
    glRotatef(90, 0, 1, 0);
    glRectf(0,0,scale.z,-scale.y);
    glPopMatrix();

    // right side
    glPushMatrix();
    glTranslatef(incr.x,incr.y,incr.z);
    glRotatef(90, 0, 1, 0);
    glRectf(0,0,scale.z,-scale.y);
    glPopMatrix();

    // top
    glPushMatrix();
    glTranslatef(incr.x,incr.y,-incr.z);
    glRotatef(-90, 0, 1, 0);
    glRotatef(90, 1, 0, 0);
    glRectf(0,0,scale.z,scale.y);
    glPopMatrix();

    glPopMatrix();
};