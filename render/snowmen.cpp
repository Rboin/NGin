//
// Created by erik on 2/22/16.
//

#include "render.h"

void render_snowmen(vec3 pos, vec3 look) {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    if (look.x)
        glRotatef(look.x, 1, 0, 0);
    if (look.y)
        glRotatef(look.y, 0, 1, 0);
    if (look.z)
        glRotatef(look.z, 0, 0, 1);

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);
    glPopMatrix();

    // Draw the head (a sphere of radius 0.25 at height 1.75)
    glPushMatrix();
    glTranslatef(0.0f, 1.7f, 0.0f); // position head
    glutSolidSphere(0.25f, 20, 20); // head sphere

    // Draw Eyes (two small black spheres)
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(0.0f, 0.10f, -0.18f); // lift eyes to final position
    glPushMatrix();
    glTranslatef(-0.05f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10); // right eye
    glPopMatrix();
    glPushMatrix();
    glTranslatef(+0.05f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10); // left eye
    glPopMatrix();
    glPopMatrix();

    // Draw Nose (the nose is an orange cone)
    glColor3f(1.0f, 0.5f, 0.5f); // nose is orange
    glPushMatrix();
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // rotate to point along -y
    glutSolidCone(0.08f, 0.5f, 10, 2); // draw cone
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}