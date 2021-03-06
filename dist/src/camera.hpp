
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "controls.hpp"
#include "easewindow.hpp"

namespace easeopengl{

    
    namespace sdjaskdbask{
        glm::vec3 position = glm::vec3(0.0f, 1.0f, 6.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        GLfloat zoom_level = 45.0f;
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

        GLfloat lastX, lastY;
        GLfloat xoffset, yoffset;
        GLfloat sensitivity = 0.1f;
        GLfloat pitch_mouse = 0.0f, yaw_mouse = -90.0f;
        bool firstMouse = true;
        bool keys[1024];

        void ___WASDcontrols(GLFWwindow* window, int key, int scancode, int action, int mode){
            if(action == GLFW_PRESS){
                keys[key] = true;
            }else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
        }



        void ___headControls(GLFWwindow* window, double xpos, double ypos){
            // first move should be smooth
            if(firstMouse){
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }
            
            // mouse calculation
            xoffset = xpos - lastX;
            yoffset = lastY - ypos;

            xoffset *= sensitivity;
            yoffset *= sensitivity;

            lastX = xpos;
            lastY = ypos;

            pitch_mouse += yoffset;
            yaw_mouse += xoffset;

            if(pitch_mouse > 89.0f)
                pitch_mouse = 89.0f;
            if(pitch_mouse < -89.0f)
                pitch_mouse = -89.0f;

            glm::vec3 fron;
            fron.x = cos(glm::radians(pitch_mouse)) * cos(glm::radians(yaw_mouse));
            fron.y = sin(glm::radians(pitch_mouse));
            fron.z = cos(glm::radians(pitch_mouse)) * sin(glm::radians(yaw_mouse));
            front = glm::normalize(fron);
        }

        void ___scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
            if(zoom_level >= 1.0f && zoom_level <= 45.0f)
                zoom_level -= yoffset;
            if(zoom_level <= 1.0f)
                zoom_level = 1.0f;
            if(zoom_level >= 45.0f)
                zoom_level = 45.0f;

        }
    }
    

    class Camera{
        GLfloat height = 2.0f;
        glm::vec3 position = glm::vec3(0.0f, this->height, 6.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        GLfloat speed = 3.0f;
        GLfloat zoom_level = 45.0f;
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

        GLfloat lastX, lastY;
        GLfloat xoffset, yoffset;
        GLfloat sensitivity = 0.1f;
        GLfloat pitch_mouse = 0.0f, yaw_mouse = -90.0f;

        glm::mat4 view;
        glm::mat4 projection;
        bool fly = false;
        bool zoom = false;
        GLfloat delta_time = 0.0f;
        GLfloat last_frame = 0.0f;
        GLfloat current_frame;

        public:

            Camera(EaseWindow3D window){
                this->lastX = (GLfloat)window.getWidth()/2;
                this->lastY = (GLfloat)window.getHeight()/2;
                this->view = glm::lookAt(this->position, this->target, this->up);
                this->projection = glm::perspective( glm::radians(this->zoom_level) , (float)window.getWidth()/(float)window.getHeight() , 0.1f , 100.0f );
            
            }

            Camera( glm::vec3 position, glm::vec3 front ,  glm::vec3 target, glm::vec3 up, GLfloat speed , EaseWindow3D window){
                this->up = up;
                this->speed = speed;
                this->position = position;
                this->target = target;
                this->front = front;
                this->lastX = (GLfloat)window.getWidth()/2;
                this->lastY = (GLfloat)window.getHeight()/2;

                this->view = glm::lookAt(this->position, this->target, this->up);
                this->projection = glm::perspective( glm::radians(this->zoom_level) , (float)window.getWidth()/(float)window.getHeight() , 0.1f , 100.0f );

            }

            void setPosition(glm::vec3 position){
                this->position = position;
                sdjaskdbask::position = this->position;
            }

            void setTarget(glm::vec3 target){
                this->target = target;
                sdjaskdbask::target = this->target;
            }

            void setSpeed(GLfloat speed){
                this->speed = speed;
            }
            void setUp(glm::vec3 up){
                this->up = up;
                sdjaskdbask::up = this->up;
            }
            void setFront(glm::vec3 front){
                this->front = front;
                sdjaskdbask::front = this->front;
            }

            void setSensitivity(GLfloat sensitivity){
                this->sensitivity = sensitivity;
                sdjaskdbask::sensitivity = this->sensitivity;
            }
            void setZoom(GLfloat zoom){
                this->zoom_level = zoom;
                sdjaskdbask::zoom_level = this->zoom_level;
            }

            void setHeight(GLfloat height){
                this->height = height;
            }

            glm::vec3 getTarget(){
                return this->target;
            }
            glm::vec3 getFront(){
                return this->front;
            }

            glm::vec3 getPosition(){
                return this->position;
            }

            void updateAll( glm::vec3 position, glm::vec3 front , glm::vec3 target, glm::vec3 up, GLfloat speed){
                this->up = up;
                this->speed = speed;
                this->position = position;
                this->target = target;
                this->front = front;
            

                sdjaskdbask::position = this->position;
                sdjaskdbask::target = this->target;
                sdjaskdbask::front = this->front;
                sdjaskdbask::up = this->up;
            }

            void update(EaseWindow3D window){
                window.useObjectShader();

                this->current_frame = glfwGetTime();
                this->delta_time = this->current_frame - this->last_frame;
                this->last_frame = this->current_frame;

                this->zoom_level = sdjaskdbask::zoom_level;
                this->position = sdjaskdbask::position;
                this->target = sdjaskdbask::target;
                this->front = sdjaskdbask::front;
                this->lastX = sdjaskdbask::lastX;
                this->lastY = sdjaskdbask::lastY;
                this->up =  sdjaskdbask::up;
                this->sensitivity = sdjaskdbask::sensitivity;

                this->view = glm::lookAt(this->position, this->target, this->up);
                this->projection = glm::perspective( glm::radians(this->zoom_level) , (float)window.getWidth()/(float)window.getHeight() , 0.1f , 100.0f );

                glUniformMatrix4fv(glGetUniformLocation(window.getObjectShader(), "projection"), 1, GL_FALSE , value_ptr(this->projection));  
                glUniformMatrix4fv(glGetUniformLocation(window.getObjectShader(), "view"), 1, GL_FALSE , value_ptr(this->view));
                glUniform3f(glGetUniformLocation(window.getObjectShader(), "camera_position"),this->position.x,this->position.y, this->position.z );
                
                window.useLightShader();
                glUniformMatrix4fv(glGetUniformLocation(window.getLightShader(), "projection"), 1, GL_FALSE , value_ptr(this->projection));  
                glUniformMatrix4fv(glGetUniformLocation(window.getLightShader(), "view"), 1, GL_FALSE , value_ptr(this->view));
            }




            void canMoveLegs(bool can){
                if(can){
                    addKeyCallBack(sdjaskdbask::___WASDcontrols);
                }
            }

            void moveLegs(){

                GLfloat speed = this->speed*this->delta_time;
                if( sdjaskdbask::keys[GLFW_KEY_W]){
                    this->position += speed * this->front;
                }
                if(sdjaskdbask::keys[GLFW_KEY_S]){
                    this->position -= speed * this->front;
                }
                if(sdjaskdbask::keys[GLFW_KEY_A]){
                    this->position -= glm::normalize(glm::cross(this->front, this->up)) * speed;
                }
                if(sdjaskdbask::keys[GLFW_KEY_D]){
                    this->position += glm::normalize(glm::cross(this->front, this->up)) * speed;
                }

                if(!this->fly)
                    this->position.y = this->height;

                sdjaskdbask::position = this->position;

            }



            void canMoveHead(bool can){
                if(can){
                    addMouseCallBack(sdjaskdbask::___headControls);
                }
            }

            void canZoom(bool can){
                if(can){
                    addScrollCallBack(sdjaskdbask::___scroll_callback);
                }
            }

            void canFly(bool can){
                this->fly = can;
            }

    };
}

#endif