#ifndef EASEWINDOW_2D_HPP
#define EASEWINDOW_2D_HPP

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<iostream>

namespace easeopengl2d{
    class EaseWindow2D{
        GLFWwindow* window;
        GLfloat width, height;
        const char* name;
        // Shader *object_vertex;
        // Shader *object_fragment;
        // GLuint object_shader;
        // GLuint light_shader;

        public:
            EaseWindow2D(GLuint width, GLuint height, const char* name){
                this->width = width;
                this->height = height;
                this->name = name;
                this->window = glfwCreateWindow(width , height , name , nullptr , nullptr);
                
                if(this->window == nullptr){
                    std::cout<<"Failed to create window"<<std::endl;
                    glfwTerminate();
                    exit(-1);
                }
            }

            ~EaseWindow2D(){}

            // void setCustomObjectShader(GLuint object_shader){
            //     this->object_shader = object_shader;
            // }

            // void useObjectShader(){
            //     glUseProgram(this->object_shader);
            // }


            // GLuint getObjectShader(){
            //     return this->object_shader;
            // }

            void use(){
                glfwMakeContextCurrent(this->window);

                // glfwSetKeyCallback(this->window, ___key_callback);
                // glfwSetCursorPosCallback(this->window, ___mouse_callback);
                // glfwSetScrollCallback(this->window, ___scroll_callback);

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

            bool isOpen(){
                return !glfwWindowShouldClose(this->window);
            }
    };
}
#endif