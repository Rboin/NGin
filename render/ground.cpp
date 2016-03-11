//
// Created by Erik on 3/9/2016.
//

#include "render.h"

void render_ground() {

    glEnable(GL_COLOR_MATERIAL);

    glColor3f(1,1,1);
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