#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

glm::mat4 Transform::calculate_model_matrix(){
    return 
        glm::translate(glm::mat4(1.0f), position)*
        glm::mat4_cast(rotation) *
        glm::scale(glm::mat4(1.0f), scale);
}

glm::mat4 Transform::get_model_matrix(){

    //return glm::mat4(1.0);

    if (!dirty)
        return modelMatrix;
    
    dirty = false;
    modelMatrix = calculate_model_matrix();
    return modelMatrix;
}

void Transform::make_dirty(){
    dirty = true;
}
