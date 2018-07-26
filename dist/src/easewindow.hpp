
#ifndef EASE_WINDOW_HPP
#define EASE_WINDOW_HPP


#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include"controls.hpp"
#include"shader.hpp"
#include "./shaders/3d/light.hpp"
#include "./shaders/3d/object.hpp"

namespace easeopengl{
    class EaseWindow{
        GLFWwindow* window;
        GLfloat width, height;
        const char* name;
        GLuint object_shader;
        GLuint light_shader;

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
            }

            ~EaseWindow(){}

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

            bool isOpen(){
                return !glfwWindowShouldClose(this->window);
            }

            void checkEvents(){
                glfwPollEvents();
            }

            void swapBuffers(){
                glfwSwapBuffers(this->window);
            }

            GLFWwindow* getWindow(){
                return this->window;
            }
    };

    class EaseWindow3D:public EaseWindow{
        Shader *object_vertex;
        Shader *object_fragment;
        Shader *light_vertex;
        Shader *light_fragment;

        public:
            EaseWindow3D(GLuint width, GLuint height, const char* name):EaseWindow(width,height,name){
            }

            void use(){
                EaseWindow::use();
                this->object_vertex = new Shader(shaders3d::vertex_object_shader, GL_VERTEX_SHADER,false);
                this->light_vertex = new Shader(shaders3d::vertex_light_shader , GL_VERTEX_SHADER,false);
                this->light_fragment = new Shader(shaders3d::fragment_light_shader , GL_FRAGMENT_SHADER,false);
                this->object_fragment = new Shader(shaders3d::fragment_object_shader , GL_FRAGMENT_SHADER, false);

                this->object_vertex->compile();
                this->object_fragment->compile();
                this->light_vertex->compile();
                this->light_fragment->compile();

                this->setCustomObjectShader(Shader::linkShaders(*this->object_vertex , *this->object_fragment));
                this->setCustomLightShader(Shader::linkShaders(*this->light_vertex , *this->light_fragment));
            }
    };

    class EaseWindow2D:public EaseWindow{
        public:
            EaseWindow2D(GLuint width, GLuint height, const char* name):EaseWindow(width,height,name){
            }
    };

}

#endif