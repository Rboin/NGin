//
// Created by Erik on 3/10/2016.
//

#include "entity.h"

void Entity::render() const {
    mat4 model = translate(m_position) * rotate(m_rotation.z, vec3(0,0,1)) * rotate(m_rotation.y, vec3(0,1,0)) * rotate(m_rotation.x, vec3(1,0,0)) * scale(m_scale);
    glUniformMatrix4fv(glGetUniformLocation(m_renderPart.shaderId, "model"), 1, GL_FALSE, value_ptr(model));
    renderPart(m_renderPart);
}
