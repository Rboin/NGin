//
// Created by Erik on 3/9/2016.
//

#include "render.h"

float green[] = { 0.1f, 0.7f, 0.2f, 1.0f };

void render_ground() {

    glEnable(GL_COLOR_MATERIAL);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
    glColor3f(0.1f,0.7f,0.2f);
    glBegin(GL_TRIANGLES);

    glVertex3f(-100.0f, -1.0f, -100.0f);
    glVertex3f(-100.0f, -1.0f,  100.0f);
    glVertex3f( 100.0f, -1.0f,  100.0f);

    glVertex3f( 100.0f, -1.0f,  100.0f);
    glVertex3f( 100.0f, -1.0f, -100.0f);
    glVertex3f(-100.0f, -1.0f, -100.0f);

    glEnd();

    glClear(GL_COLOR_MATERIAL);

};