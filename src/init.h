#ifndef INIT_H
#define INIT_H

#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<iostream>
using namespace std;

namespace easeopengl{
    void init(GLuint version){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    GLFWwindow* createWindow(GLuint width, GLuint height, const char* name){
    GLFWwindow *window = glfwCreateWindow(width , height , name , nullptr , nullptr);
        if(window == nullptr){
            cout<<"Failed to create window"<<endl;
            glfwTerminate();
            exit(-1);
        }
        return window;
    }

    void useWindow(GLFWwindow* window){
        glfwMakeContextCurrent(window);
        
        glewExperimental = GL_TRUE;
        glewInit();

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);  
        glViewport(0, 0, width, height);
    }
}

#endif