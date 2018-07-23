#ifndef INIT_HPP
#define INIT_HPP

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

namespace easeopengl2d{
    void init(GLuint version){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void end(){
        glfwTerminate();
    }
}


#endif