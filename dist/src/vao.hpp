
#ifndef VAO_HPP
#define VAO_HPP
#include "vbo.hpp"
#include "ebo.hpp"

namespace easeopengl{

    template<class Data, class Data2>
    class VAO{
        GLuint vao;
        VBO<Data> *vbo;
        EBO<Data2> *ebo;
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

            void bindEBO(Data2 data[] , GLuint data_length){
                this->ebo = new EBO<Data2>(data, data_length);
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

            GLuint getVAOdataLength(){
                return this->vao_data_length;
            }

    };
}
#endif