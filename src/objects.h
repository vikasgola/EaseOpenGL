
#ifndef OBJECTS_H
#define OBJECTS_H

#include<GL/glew.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "vao.h"

namespace easeopengl{
    class EaseObject{
        public:
            GLfloat *vertices;
            GLuint number_of_vertices;
            GLint *indices;
            glm::vec3 color ;
            VAO<GLfloat, GLint> *vao;
            glm::mat4 model;
            glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
            glm::vec3 rotation_axis = glm::vec3(0.0f,0.0f,1.0f);
            GLfloat angle = 0.0f;
            
            EaseObject(GLuint point_length , GLfloat _vertices[], GLuint number_of_vertices, GLint _indices[] = nullptr,  GLuint number_of_indices = 0, glm::vec3 _color = glm::vec3(0.0f,0.0f,0.0f)){
                this->vertices = _vertices;
                this->indices = _indices;
                this->color = _color;
                this->number_of_vertices = number_of_vertices;

                this->vao = new VAO<GLfloat, GLint>(point_length);
                
                this->vao->bindVBO(this->vertices ,  this->number_of_vertices);
                this->vao->setVBOVertexAttrib(0,3,0);
                if(point_length == 5){
                    this->vao->setVBOVertexAttrib(2,2,3);
                }
                if(point_length == 6){
                    this->vao->setVBOVertexAttrib(1,3,3);
                }

                if(this->indices != nullptr){
                    this->vao->bindEBO(this->indices, number_of_indices);
                }

                this->vao->unbind();

            }

            void draw(GLint draw_using,GLuint shader_program){
                if(this->indices == nullptr){
                    glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE , value_ptr(this->model));
                    glUniform3f(glGetUniformLocation(shader_program, "object_color"), this->color.r,this->color.g,this->color.b);
                    glBindVertexArray(this->vao->getVAO());
                    glDrawArrays(draw_using , 0 , this->number_of_vertices/this->vao->getVAOdataLength());
                    glBindVertexArray(0);
                }

            }

            void setColor(GLfloat r,GLfloat g, GLfloat b ){
                this->color = glm::vec3(r,g,b);
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