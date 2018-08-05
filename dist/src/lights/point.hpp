
#ifndef POINT_HPP
#define POINT_HPP

#include "../easewindow.hpp"
#include "../objects.hpp"
#include "light.hpp"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace easeopengl{
    class PointLight:public Light{
        public:
            PointLight(glm::vec3 color, glm::vec3 position, glm::vec3 attenuation):Light(color, position){
                this->constant = attenuation.x;
                this->linear = attenuation.y;
                this->quadratic = attenuation.z;
            }

            void setAttenuation(GLfloat c, GLfloat l, GLfloat q){
                this->constant = c;
                this->linear = l;
                this->quadratic = q;
            }
    
    };
}

#endif