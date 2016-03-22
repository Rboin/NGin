//
// Created by Erik on 3/21/2016.
//

#include "material.h"

void drawMaterial (const Material &material, const GLuint shader) {
    glUniform3fv(glGetUniformLocation(shader, "ambient"), 1, value_ptr(material.ambient));
    glUniform3fv(glGetUniformLocation(shader, "diffuse"), 1, value_ptr(material.diffuse));
    glUniform3fv(glGetUniformLocation(shader, "specular"), 1, value_ptr(material.specular));
    glUniform1f(glGetUniformLocation(shader, "power"), material.power);
}
