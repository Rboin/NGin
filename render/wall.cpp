//
// Created by erik on 3/11/16.
//

#include "render.h"

void render_wall(vec3 pos, vec3 look) {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    if (look.x)
        glRotatef(look.x, 1, 0, 0);
    if (look.y)
        glRotatef(look.y, 0, 1, 0);
    if (look.z)
        glRotatef(look.z, 0, 0, 1);

    glColor3f(.8f, .8f, .8f);

    // front
    glPushMatrix();
    glTranslatef(.15f,0,.15f);
    glRectf(0, 0, -2, -2);
    glPopMatrix();

    // back
    glPushMatrix();
    glTranslatef(.15f,0,-.15f);
    glRectf(0, 0, -2, -2);
    glPopMatrix();

    // left side
    glPushMatrix();
    glTranslatef(.15f,-2,.15f);
    glRotatef(90, 0, 1, 0);
    glRectf(0,0,.3f,2);
    glPopMatrix();

    // right side
    glPushMatrix();
    glTranslatef(-1.85f,-2,.15f);
    glRotatef(90, 0, 1, 0);
    glRectf(0,0,.3f,2);
    glPopMatrix();

    // top
    glPushMatrix();
    glTranslatef(-1.85f,0,.15f);
    glRotatef(90, 0, 1, 0);
    glRotatef(90, 1, 0, 0);
    glRectf(0,0,.3f,2);
    glPopMatrix();

    glPopMatrix();
};