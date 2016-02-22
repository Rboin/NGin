//
// Created by erik on 2/22/16.
//

#include "render.h"

void render_outlaw(vec3 position, vec3 look) {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    if (look.x)
        glRotatef(look.x, 1, 0, 0);
    if (look.y)
        glRotatef(look.y, 0, 1, 0);
    if (look.z)
        glRotatef(look.z, 0, 0, 1);

    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.75);
    glutSolidSphere(0.75, 20, 20);
    glPopMatrix();

    // Draw the head (a sphere of radius 0.25 at height 1.75)
    glPushMatrix();
    glTranslatef(0.0, 0.0, 1.75); // position head
    glutSolidSphere(0.25, 20, 20); // head sphere

    // Draw Eyes (two small white spheres)
    glColor3f(1.0, 1.0, 1.0); // set drawing color to white
    glPushMatrix();
    glTranslatef(0.0, -0.18, 0.10); // lift eyes to final position
    glPushMatrix();
    glTranslatef(-0.05, 0.0, 0.0);
    glutSolidSphere(0.05, 10, 10); // right eye
    glPopMatrix();
    glPushMatrix();
    glTranslatef(+0.05, 0.0, 0.0);
    glutSolidSphere(0.05, 10, 10); // left eye
    glPopMatrix();
    glPopMatrix();

    // Draw Nose (the nose is an orange cone)
    glColor3f(1.0, 0.5, 0.5); // nose is orange
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0); // rotate to point along -y
    glutSolidCone(0.08, 0.5, 10, 2); // draw cone
    glPopMatrix();
    glPopMatrix();

    // Draw a faux shadow beneath snow man (dark green circle)
    glColor3f(0.0, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(0.2, 0.2, 0.001);    // translate to just above ground
    glScalef(1.0, 1.0, 0.0); // scale sphere into a flat pancake
    glutSolidSphere(0.75, 20, 20); // shadow same size as body
    glPopMatrix();

    glPopMatrix();
}