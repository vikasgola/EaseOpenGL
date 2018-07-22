
#ifndef OBJECTS_H
#define OBJECTS_H

#include<GL/glew.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "vao.h"

namespace easeopengl{
    class EaseObject{
            GLfloat *vertices;
            GLuint number_of_vertices;
            GLint *indices;
            VAO<GLfloat, GLint> *vao;
            glm::mat4 model;
            glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
            glm::vec3 rotation_axis = glm::vec3(0.0f,0.0f,1.0f);
            GLfloat angle = 0.0f;
            
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
            float shininess = 32.0f;

        public:
            EaseObject(GLuint point_length, GLint id , GLfloat _vertices[], GLuint number_of_vertices, glm::vec3 _color = glm::vec3(1.0f,1.0f,1.0f), GLint _indices[] = nullptr,  GLuint number_of_indices = 0){
                this->vertices = _vertices;
                this->indices = _indices;
                this->number_of_vertices = number_of_vertices;

                this->ambient = _color;
                this->diffuse = _color;
                this->specular = _color;
                
                this->vao = new VAO<GLfloat, GLint>(point_length);
                
                this->vao->bindVBO(this->vertices ,  this->number_of_vertices);
                this->vao->setVBOVertexAttrib(0,3,0);
                if(id == 02 || id == 023 || id == 012 || id == 0123){
                    this->vao->setVBOVertexAttrib(2,2,3);
                }
                if(id == 01 || id == 012 || id == 0123 || id == 013){
                    this->vao->setVBOVertexAttrib(1,3,3);
                }
                if(id == 013 || id == 0123 || id == 023 || id == 03){
                    this->vao->setVBOVertexAttrib(3,3,3);
                }

                if(this->indices != nullptr){
                    this->vao->bindEBO(this->indices, number_of_indices);
                }

                this->vao->unbind();

            }

            void draw(GLint draw_using, EaseWindow window, bool isLight=false){
                if(isLight){
                    window.useLightShader();
                    glUniform3f(glGetUniformLocation(window.getLightShader(), "object_color"), this->diffuse.r,this->diffuse.g,this->diffuse.b);
                    glUniformMatrix4fv(glGetUniformLocation(window.getLightShader(), "model"), 1, GL_FALSE , value_ptr(this->model));

                    glBindVertexArray(this->vao->getVAO());
                    glDrawArrays(draw_using , 0 , this->number_of_vertices/this->vao->getVAOdataLength());
                    glBindVertexArray(0);
                }else if(this->indices == nullptr){
                    window.useObjectShader();
                    glUniformMatrix4fv(glGetUniformLocation(window.getObjectShader(), "model"), 1, GL_FALSE , value_ptr(this->model));
                    glUniform3f(glGetUniformLocation(window.getObjectShader(), "material.ambient"), this->ambient.r,this->ambient.g,this->ambient.b);
                    glUniform3f(glGetUniformLocation(window.getObjectShader(), "material.diffuse"), this->diffuse.r,this->diffuse.g,this->diffuse.b);
                    glUniform3f(glGetUniformLocation(window.getObjectShader(), "material.specular"), this->specular.r,this->specular.g,this->specular.b);
                    glUniform1f(glGetUniformLocation(window.getObjectShader(), "material.shininess"), this->shininess);
                    
                    glBindVertexArray(this->vao->getVAO());
                    glDrawArrays(draw_using , 0 , this->number_of_vertices/this->vao->getVAOdataLength());
                    glBindVertexArray(0);
                }

            }

            void setApperance(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular){
                this->ambient = ambient;
                this->specular = specular;
                this->diffuse = diffuse;
            }

            void setShininess(GLfloat shininess){
                this->shininess = shininess;
            }

            glm::vec3 getAmbient(){
                return this->ambient;
            }

            glm::vec3 getDiffuse(){
                return this->diffuse;
            }

            void setSpecular(glm::vec3 specular){
                this->specular = specular;
            }

            void setAmbient(glm::vec3 ambient){
                this->ambient = ambient;
            }

            void setDiffuse(glm::vec3 diffuse){
                this->diffuse = diffuse;
            }

            glm::vec3 getSpecular(){
                return this->specular;
            }

            glm::vec3 getPosition(){
                return this->position;
            }

            void setPosition(glm::vec3 translate_position){
                this->position = translate_position;    
                this->model = glm::translate(this->model, this->position);
            }

            void setRotation(GLfloat rotate_angle, glm::vec3 rotation_axis = glm::vec3(0.0f,0.0f,1.0f)){
                this->angle = rotate_angle;
                this->rotation_axis = rotation_axis;
                this->model = glm::rotate(this->model , this->angle , this->rotation_axis);
            }

            void setScale(GLfloat x,GLfloat y, GLfloat z){
                this->model = glm::scale(this->model,glm::vec3(x,y,z));
            }

            void clearModel(){
                this->model = glm::mat4();
            }
    };

}

#endif