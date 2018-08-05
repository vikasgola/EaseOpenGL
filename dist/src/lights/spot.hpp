
#ifndef SPOT_HPP
#define SPOT_HPP

#include "../easewindow.hpp"
#include "../objects.hpp"
#include "light.hpp"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace easeopengl{
    class SpotLight:public Light{
        GLfloat cutoff,outerCutOff;
        glm::vec3 direction;
        public:
            SpotLight(glm::vec3 color, glm::vec3 position, glm::vec3 direction ,GLfloat angle):Light(color, position){
                this->cutoff = angle;
                this->outerCutOff = angle + 5.0f;
                this->direction = direction;
            }

            void setDirection(glm::vec3 direction, EaseWindow3D window){
                this->direction = direction;
            }

            void on(EaseWindow3D window){
                window.useObjectShader();
                glUniform1f(glGetUniformLocation(window.getObjectShader(), "light.cutOff"),glm::cos(glm::radians(this->cutoff)));
                glUniform1f(glGetUniformLocation(window.getObjectShader(), "light.outerCutOff"),glm::cos(glm::radians(this->outerCutOff)));
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "light.direction"), this->direction.x, this->direction.y, this->direction.z);
                Light::on(window);
            }
    };
}

#endif