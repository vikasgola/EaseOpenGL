
#ifndef VBO_H
#define VBO_H


#include<GL/glew.h>

#include<iostream>
#include<fstream>

template<class Data>
class VBO{
    GLuint vbo;
    Data *vbo_data;
    GLuint vbo_data_length;

    public:
        GLuint getVBO(){
            return this->vbo;
        }

        Data getVBOData(){
            return this->vbo_data;
        }
        
        VBO(Data data , GLuint data_length){
            this->vbo_data = data;
            this->vbo_data_length = data_length;

            glGenBuffers(1, &this->vbo);
            glBindBuffer(GL_ARRAY_BUFFER,this->vbo);
            glBufferData(GL_ARRAY_BUFFER, this->vbo_data_length*sizeof(this->vbo_data), this->vbo_data, GL_STATIC_DRAW);
        }

        void setVertexAttrib(GLuint location, GLuint size, GLuint offset){
            cout<<sizeof(Data)<<endl;
            glVertexAttribPointer(location , size , GL_FLOAT , GL_FALSE, vbo_data_length*sizeof(Data), (GLvoid*)(offset * sizeof(Data)));
            glEnableVertexAttribArray(location);
        }

        void unbind(){
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

};

#endif