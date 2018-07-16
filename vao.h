
#ifndef VAO_H
#define VAO_H


#include<GL/glew.h>

#include<iostream>
#include<fstream>


class VAO{
    GLuint vao;

    public:
        VAO(){
            glGenVertexArrays(1, &this->vao);
            glBindVertexArray(this->vao);
        }

        void unbind(){
            glBindVertexArray(0);
        }

};

#endif