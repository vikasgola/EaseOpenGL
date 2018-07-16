
#ifndef SHADER_H
#define SHADER_H

#include<GL/glew.h>

#include<iostream>
#include<fstream>
using namespace std;

class Shader{
    const char* shader_filename;
    GLuint shader;

    public:
        string readShader(const char *filePath) {
            string content;
            ifstream fileStream(filePath, ios::in);

            if(!fileStream.is_open()) {
                cerr << "Could not read file " << filePath << ". File does not exist." << endl;
                return "";
            }

            while(!fileStream.eof()) {
                string line = "";
                getline(fileStream, line);
                content.append(line + "\n");
            }

            fileStream.close();
            return content;
        }
    
        Shader(const char* filename){
            this->shader_filename = filename;
            string shader_string = readShader(this->shader_filename);

            const GLchar *shader_source = shader_string.c_str();
            this->shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(this->shader , 1 , &shader_source , NULL);
        }

        ~Shader(){
            glDeleteShader(this->shader);
        }

        void compile(){
            glCompileShader(this->shader);
            
            GLint success;
            GLchar infolog[512];
            glGetShaderiv(this->shader , GL_COMPILE_STATUS , &success);

            // checking compiling status of vertex shader
            if(!success){
                glGetShaderInfoLog(this->shader , 512 , NULL , infolog);
                cout<<"Error::shader::vertex:: compilation failed\n"<<infolog<<endl;
            }
        }

        GLuint getShader(){
            return this->shader;
        }

        const char* getShaderFilename(){
            return this->shader_filename;
        }

        GLuint static linkShaders(GLuint shaders[] , int number_of_shaders){
            GLuint shader_program = glCreateProgram();

            for(int i=0;i<number_of_shaders;i++){
                glAttachShader(shader_program,shaders[i]);
            }
            glLinkProgram(shader_program);

            // status of shader program and linking
            GLint success;
            GLchar infolog[512];
            glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(shader_program, 512, NULL, infolog);
                cout<<"Error::shader::Linking failed\n"<<infolog<<endl;
            }
            return shader_program;
        } 
        
};

#endif