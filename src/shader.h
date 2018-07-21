
#ifndef SHADER_H
#define SHADER_H

#include<fstream>
namespace easeopengl{

    class Shader{
        const char* shader_filename;
        GLuint shader;

        public:
            std::string readShader(const char *filePath) {
                std::string content;
                std::ifstream fileStream(filePath, std::ios::in);

                if(!fileStream.is_open()) {
                    std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
                    return "";
                }

                while(!fileStream.eof()) {
                    std::string line = "";
                    std::getline(fileStream, line);
                    content.append(line + "\n");
                }

                fileStream.close();
                return content;
            }
        
            Shader(const char* filename, GLuint shader_type){
                this->shader_filename = filename;
                std::string shader_string = readShader(this->shader_filename);

                const GLchar *shader_source = shader_string.c_str();
                this->shader = glCreateShader(shader_type);
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
                    std::cout<<"Error::shader::vertex:: compilation failed\n"<<infolog<<std::endl;
                }
            }

            GLuint getShader(){
                return this->shader;
            }

            const char* getShaderFilename(){
                return this->shader_filename;
            }

            GLuint static linkShaders(Shader shader1, Shader shader2 ){
                GLuint shader_program = glCreateProgram();

                glAttachShader(shader_program,shader1.getShader());
                glAttachShader(shader_program,shader2.getShader());
                glLinkProgram(shader_program);

                // status of shader program and linking
                GLint success;
                GLchar infolog[512];
                glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
                if(!success) {
                    glGetProgramInfoLog(shader_program, 512, NULL, infolog);
                    std::cout<<"Error::shader::Linking failed\n"<<infolog<<std::endl;
                }
                return shader_program;
            } 
            
    };
}
#endif