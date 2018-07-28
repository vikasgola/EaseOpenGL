#ifndef SHAPE_HPP
#define SHAPE_HPP

#include<GL/glew.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "../easewindow.hpp"
#include "../vao.hpp"
#include "../texture.hpp"

namespace easeopengl{
    class EaseShape{
        private:
            VAO<GLfloat, GLuint> *vao;
            glm::mat4 model;
            glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
            glm::vec3 rotation_axis = glm::vec3(0.0f,0.0f,1.0f);
            GLfloat angle = 0.0f;
            glm::vec3 color = glm::vec3(1.0f);
            Texture *texture = nullptr;
            bool isFill = true;

        protected:
            GLuint *indices = nullptr;
            GLuint number_of_vertices , number_of_indices = 0;
            GLfloat *vertices;

            EaseShape(){}

            void createShape(GLfloat _vertices[], GLuint _indices[] = nullptr){
                this->vertices = _vertices;
                this->indices = _indices;
                
                this->vao = new VAO<GLfloat, GLuint>(2);

                this->vao->bindVBO(this->vertices ,  this->number_of_vertices);
                this->vao->setVBOVertexAttrib(0,2,0);

                if(this->number_of_indices){
                    this->vao->bindEBO(this->indices, this->number_of_indices);
                }

                this->vao->unbind();
            }
        
        
        public:
            EaseShape(GLfloat _vertices[], GLuint number_of_vertices, glm::vec3 _color = glm::vec3(1.0f), GLuint _indices[] = nullptr,  GLuint number_of_indices = 0){
                this->vertices = _vertices;
                this->indices = _indices;
                this->number_of_vertices = number_of_vertices;
                this->color = _color;
                this->number_of_indices = number_of_indices;

                this->vao = new VAO<GLfloat, GLuint>(2);
                
                this->vao->bindVBO(this->vertices ,  this->number_of_vertices);
                this->vao->setVBOVertexAttrib(0,2,0);

                if(this->number_of_indices){
                    this->vao->bindEBO(this->indices, this->number_of_indices);
                }

                this->vao->unbind();

            }

            void noFill(){
                this->isFill = false;
            }

            void fill(){
                this->isFill = true;
            }

            void addTexture(const char* filename){
                this->texture = new Texture(filename);
                this->texture->generate();
            }

            void removeTexture(){
                this->texture = nullptr;
            }

            void draw(GLint draw_using, EaseWindow2D window){
                window.useObjectShader();

                if(isFill){
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }else{
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }

                glUniform3f(glGetUniformLocation(window.getObjectShader(), "object_color"), this->color.r,this->color.g,this->color.b);
                glUniformMatrix4fv(glGetUniformLocation(window.getObjectShader(), "model"), 1, GL_FALSE , value_ptr(this->model));
                
                if(!this->number_of_indices){
                    glBindVertexArray(this->vao->getVAO());
                    glDrawArrays(draw_using , 0 , this->number_of_vertices/this->vao->getVAOdataLength());
                    glBindVertexArray(0);
                }else{
                    glBindVertexArray(this->vao->getVAO());
                    glDrawElements(draw_using ,this->number_of_indices ,GL_UNSIGNED_INT,0);
                    glBindVertexArray(0);
                }
            }

            void setColor(GLfloat r,GLfloat g, GLfloat b){
                this->color = glm::vec3(r,g,b);
            }

            glm::vec3 getPosition(){
                return this->position;
            }

            void translate(GLfloat x,GLfloat y){
                this->position = glm::vec3(x,y,0.0f);
                this->model = glm::translate(this->model, this->position);
            }

            void rotate(GLfloat rotate_angle, glm::vec3 rotation_axis = glm::vec3(0.0f,0.0f,1.0f)){
                this->angle = rotate_angle;
                this->rotation_axis = rotation_axis;
                this->model = glm::rotate(this->model , this->angle , this->rotation_axis);
            }

            void setScale(GLfloat x,GLfloat y){
                this->model = glm::scale(this->model,glm::vec3(x,y,1.0f));
            }

            void clearModel(){
                this->model = glm::mat4();
            }
    };
}

#endif