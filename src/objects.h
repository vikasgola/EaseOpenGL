
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
            glm::vec3 color;
            VAO<GLfloat, GLint> *vao;
            
            EaseObject(GLuint point_length , GLfloat _vertices[], GLuint number_of_vertices, GLint _indices[] = nullptr,  GLuint number_of_indices = 0, glm::vec3 _color = glm::vec3(1.0f,1.0f,1.0f)){
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

            void draw(GLint draw_using){
                if(this->indices == nullptr){
                    glBindVertexArray(this->vao->getVAO());
                    glDrawArrays(draw_using , 0 , this->number_of_vertices/this->vao->getVAOdataLength());
                    glBindVertexArray(0);
                }
            }
    };

}

#endif