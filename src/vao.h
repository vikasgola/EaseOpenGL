
#ifndef VAO_H
#define VAO_H
#include "vbo.h"
#include "ebo.h"

namespace easeopengl{

    template<class Data>
    class VAO{
        GLuint vao;
        VBO<Data> *vbo;
        EBO<Data> *ebo;
        GLuint vao_data_length;

        public:
            VAO(GLuint data_length){
                glGenVertexArrays(1, &this->vao);
                glBindVertexArray(this->vao);
                this->vao_data_length = data_length;
            }

            void bindVBO(Data data[] , GLuint data_length){
                this->vbo = new VBO<Data>(data, data_length);
            }

            void setVBOVertexAttrib(GLuint location, GLuint size, GLuint offset){
                this->vbo->setVertexAttrib(location , size , offset, this->vao_data_length);
            }

            void bindEBO(Data data[] , GLuint data_length){
                this->ebo = new EBO<Data>(data, data_length);
            }

            void unbind(){
                this->vbo->unbind();
                glBindVertexArray(0);
                if(this->ebo != nullptr)
                    this->ebo->unbind();
            }

            GLuint getVAO(){
                return this->vao;
            }

    };
}
#endif