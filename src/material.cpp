/*
 *  Modern OpenGL Game Engine C/C++
 *  Copyright (C) 2016  Erik Nijenhuis

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <ngin.h>
#include <glm/ext.hpp>

using namespace NGin;

void Model::setMaterial (const Model::Material &material, const GLuint shader) {
    glUniform3fv(glGetUniformLocation(shader, "ambient"), 1, glm::value_ptr(material.ambient));
    glUniform3fv(glGetUniformLocation(shader, "diffuse"), 1, glm::value_ptr(material.diffuse));
    glUniform3fv(glGetUniformLocation(shader, "specular"), 1, glm::value_ptr(material.specular));
    glUniform1f(glGetUniformLocation(shader, "power"), material.power);
}
