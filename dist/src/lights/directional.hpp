
#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "../easewindow.hpp"
#include "../objects.hpp"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace easeopengl{
    class DirectionalLight{
        glm::vec3 direction;
        glm::vec3 ambient, diffuse,specular;
        
        public:
            DirectionalLight(glm::vec3 color, glm::vec3 direction){
                this->ambient = glm::vec3(0.4f);
                this->diffuse = color;
                this->specular = glm::vec3(1.0f);
            }

            void setDirection(glm::vec3 direction, EaseWindow3D window){
                this->direction = direction;
            }

            void setProperties(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, EaseWindow3D window){
                this->ambient = ambient;
                this->diffuse = diffuse;
                this->specular = specular;
            }

            void on(EaseWindow3D window){
                window.useObjectShader();
                glm::vec3 a = this->ambient;
                glm::vec3 d = this->diffuse;
                glm::vec3 s = this->specular;
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "light.ambient"), a.x,a.y,a.z );
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "light.diffuse"), d.r,d.g,d.b);
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "light.specular"), s.r,s.g,s.b);

                glm::vec3 pos = this->direction;
                glUniform1i(glGetUniformLocation(window.getObjectShader(), "light.isDirectional"), 1);
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "light.direction"), pos.x, pos.y, pos.z);
            }

            void off(EaseWindow3D window){
                window.useObjectShader();
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "light.ambient"), 0.0f, 0.0f, 0.0f);
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "light.diffuse"), 0.0f, 0.0f, 0.0f);
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "light.specular"), 0.0f, 0.0f, 0.0f);
            }
    };
}

#endif