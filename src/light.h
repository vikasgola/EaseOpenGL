
#ifndef LIGHT_H
#define LIGHT_H

#include "objects.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace easeopengl{
    class Light{
        EaseObject *light;
        glm::vec3 color;
        GLfloat vertices[108] = {
            -0.5f, -0.5f, -0.5f, 
            0.5f, -0.5f, -0.5f, 
            0.5f,  0.5f, -0.5f, 
            0.5f,  0.5f, -0.5f, 
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f, 

            -0.5f, -0.5f,  0.5f, 
            0.5f, -0.5f,  0.5f, 
            0.5f,  0.5f,  0.5f, 
            0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f, 

            -0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f, 

            0.5f,  0.5f,  0.5f, 
            0.5f,  0.5f, -0.5f, 
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f, 
            0.5f,  0.5f,  0.5f, 

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f, 
            0.5f, -0.5f,  0.5f, 
            0.5f, -0.5f,  0.5f, 
            -0.5f, -0.5f,  0.5f, 
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f, 
            0.5f,  0.5f,  0.5f, 
            0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f, -0.5f
        };
        
        public:
            Light(glm::vec3 color, glm::vec3 position){
                this->light = new EaseObject(3, 0,this->vertices,108);
                this->light->clearModel();
                this->light->setPosition(position);
                this->light->setScale(0.2f,0.2f,0.2f);
                this->color = color;
                this->light->setColor(color.r,color.g,color.b);
            }

            void setPosition(glm::vec3 position){
                this->light->setPosition(position);
            }

            void setRotation(GLfloat rotate_angle , glm::vec3 rotation_axis){
                this->light->setRotation(rotate_angle,rotation_axis);
            }

            void setColor(GLfloat r ,GLfloat g , GLfloat b){
                this->light->setColor(r, g , b);
                this->color = this->light->getColor();
            }

            void clearModel(){
                this->light->clearModel();
            }

            void show(EaseWindow window){
                window.useLightShader();
                this->light->draw(GL_TRIANGLES, window , true);
            }

            void on(EaseWindow window){
                window.useLightShader();
                glUniform3f(glGetUniformLocation(window.getLightShader(), "light_color"), this->color.r, this->color.g, this->color.b);
                glm::vec3 pos = this->light->getPosition();
                glUniform3f(glGetUniformLocation(window.getLightShader(), "light_position"), pos.x, pos.y, pos.z);
            }

            void off(EaseWindow window){
                window.useLightShader();
                glUniform3f(glGetUniformLocation(window.getLightShader(), "light_color"), 0.0f, 0.0f, 0.0f);
            }
    };
}

#endif