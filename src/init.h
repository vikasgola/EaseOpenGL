#ifndef INIT_H
#define INIT_H

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"controls.h"

#include<iostream>
using namespace std;

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
        public:
            EaseWindow(GLuint width, GLuint height, const char* name){
                this->width = width;
                this->height = height;
                this->name = name;
                this->window = glfwCreateWindow(width , height , name , nullptr , nullptr);
                
                if(this->window == nullptr){
                    cout<<"Failed to create window"<<endl;
                    glfwTerminate();
                    exit(-1);
                }
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

            GLFWwindow* getWindow(){
                return this->window;
            }
    };

    void endProgram(){
        glfwTerminate();
    }
}

#endif