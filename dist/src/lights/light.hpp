
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "../easewindow.hpp"
#include "../objects.hpp"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace easeopengl{
    class Light{
        EaseObject *light;
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

        protected:
            GLfloat constant = 1.0f,linear = 0.0f,quadratic = 0.0f;
        
        public:
            Light(glm::vec3 color, glm::vec3 position){
                this->light = new EaseObject(3,0,this->vertices,108);
                this->light->clearModel();
                this->light->translate(position);
                // this->light->scale(0.1f,0.1f,0.1f);
                this->light->setApperance(glm::vec3(0.2f),color,glm::vec3(1.0f));
            
            }

            void setPosition(glm::vec3 position, EaseWindow3D window){
                this->light->translate(position);
            }

            void setRotation(GLfloat rotate_angle , glm::vec3 rotation_axis){
                this->light->rotate(rotate_angle,rotation_axis);
            }

            void setProperties(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, EaseWindow3D window){
                this->light->setApperance(ambient,diffuse,specular);
            }

            void clearModel(){
                this->light->clearModel();
            }

            void show(EaseWindow3D window){
                this->light->draw(GL_TRIANGLES, window , true);
            }

            void on(EaseWindow3D window){
                window.useObjectShader();
                glUniform1i(glGetUniformLocation(window.getObjectShader(), "light.isDirectional"), 0);
                glm::vec3 a = this->light->getAmbient();
                glm::vec3 d = this->light->getDiffuse();
                glm::vec3 s = this->light->getSpecular();
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "light.ambient"), a.x,a.y,a.z );
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "light.diffuse"), d.r,d.g,d.b);
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "light.specular"), s.r,s.g,s.b);

                glUniform1f(glGetUniformLocation(window.getObjectShader(), "light.constant"),this->constant);
                glUniform1f(glGetUniformLocation(window.getObjectShader(), "light.linear"),this->linear);
                glUniform1f(glGetUniformLocation(window.getObjectShader(), "light.quadratic"), this->quadratic);


                glm::vec3 pos = this->light->getPosition();
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "light.position"), pos.x, pos.y, pos.z);
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