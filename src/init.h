#ifndef INIT_H
#define INIT_H

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"controls.h"
#include"shader.h"

#include<iostream>

namespace easeopengl{
    void init(GLuint version){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    class EaseWindow{
        GLFWwindow* window;
        GLfloat width, height;
        const char* name;
        Shader *object_vertex;
        Shader *object_fragment;
        Shader *light_vertex;
        Shader *light_fragment;
        GLuint object_shader;
        GLuint light_shader;
        bool isOpen = true;

        public:
            EaseWindow(GLuint width, GLuint height, const char* name){
                this->width = width;
                this->height = height;
                this->name = name;
                this->window = glfwCreateWindow(width , height , name , nullptr , nullptr);
                
                if(this->window == nullptr){
                    std::cout<<"Failed to create window"<<std::endl;
                    glfwTerminate();
                    exit(-1);
                }

                this->object_vertex = new Shader("./shaders/object/vertex_shader.glsl", GL_VERTEX_SHADER);
                this->light_vertex = new Shader("./shaders/light/vertex_shader.glsl", GL_VERTEX_SHADER);
                this->light_fragment = new Shader("./shaders/light/fragment_shader.glsl" , GL_FRAGMENT_SHADER);
                this->light_fragment = new Shader("./shaders/object/fragment_shader.glsl" , GL_FRAGMENT_SHADER);

                this->object_vertex->compile();
                this->object_fragment->compile();
                this->light_vertex->compile();
                this->light_fragment->compile();

                this->object_shader = Shader::linkShaders(*this->object_vertex , *this->object_fragment);
                this->light_shader  =  Shader::linkShaders(*this->light_vertex , *this->light_fragment);
            }

            ~EaseWindow(){
                this->isOpen = false;
                delete this->object_vertex;
                delete this->object_fragment;
                delete this->light_fragment;
                delete this->light_vertex;
            }

            void setCustomLightShader(GLuint light_shader){
                this->light_shader = light_shader;
            }

            void setCustomObjectShader(GLuint object_shader){
                this->object_shader = object_shader;
            }

            void useLightShader(){
                glUseProgram(this->light_shader);
            }

            void useObjectShader(){
                glUseProgram(this->object_shader);
            }

            GLuint getLightShader(){
                return this->light_shader;
            }

            GLuint getObjectShader(){
                return this->object_shader;
            }

            void use(){
                glfwMakeContextCurrent(this->window);

                glfwSetKeyCallback(this->window, ___key_callback);
                glfwSetCursorPosCallback(this->window, ___mouse_callback);
                glfwSetScrollCallback(this->window, ___scroll_callback);

                glewExperimental = GL_TRUE;
                glewInit();
                glViewport(0, 0, this->width, this->height);
            }

            void update(){
                int width, height;
                glfwGetFramebufferSize(this->window, &width, &height);  
                glViewport(0,0,width,height);
                this->width = width;
                this->height = height;        
            }
            
            int getWidth(){
                int width, height;
                glfwGetFramebufferSize(window, &width, &height);  
                return width;
            }

            int getHeight(){
                int width, height;
                glfwGetFramebufferSize(window, &width, &height);  
                return height;
            }

            void clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
                    glClearColor(r,g,b,a);
            }

            void clear(){
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
            }

            GLFWwindow* getWindow(){
                return this->window;
            }
    };

    void endProgram(){
        glfwTerminate();
    }
}

#endif