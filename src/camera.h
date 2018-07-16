
#ifndef CAMERA_H
#define CAMERA_H

#include "init.h"
#include "controls.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace easeopengl{

    
    namespace sdjaskdbask{
        glm::vec3 position = glm::vec3(0.0f, 1.0f, 6.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        GLfloat speed = 5.0f;
        GLfloat zoom_level = 45.0f;
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

        GLfloat lastX, lastY;
        GLfloat xoffset, yoffset;
        GLfloat sensitivity = 0.08f;
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

            glm::vec3 front;
            front.x = cos(glm::radians(pitch_mouse)) * cos(glm::radians(yaw_mouse));
            front.y = sin(glm::radians(pitch_mouse));
            front.z = cos(glm::radians(pitch_mouse)) * sin(glm::radians(yaw_mouse));
            front = glm::normalize(front);
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
        glm::vec3 position = glm::vec3(0.0f, 1.0f, 6.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        GLfloat speed = 5.0f;
        GLfloat zoom_level = 45.0f;
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

        GLfloat lastX, lastY;
        GLfloat xoffset, yoffset;
        GLfloat sensitivity = 0.08f;
        GLfloat pitch_mouse = 0.0f, yaw_mouse = -90.0f;
        bool firstMouse = true;

        glm::mat4 view;
        glm::mat4 projection;
        bool keys[1024];
        bool fly = false;
        bool zoom = false;

        public:
            Camera(EaseWindow window){
                this->lastX = (GLfloat)window.getWidth()/2;
                this->lastY = (GLfloat)window.getHeight()/2;
                this->view = glm::lookAt(this->position, this->target, this->up);
                this->projection = glm::perspective( glm::radians(this->zoom_level) , (float)window.getWidth()/(float)window.getHeight() , 0.1f , 100.0f );
            }

            Camera( glm::vec3 position, glm::vec3 front ,  glm::vec3 target, glm::vec3 up, GLfloat speed , EaseWindow window){
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

            void updatePosition(glm::vec3 position){
                this->position = position;
            }
            void updateTarget(glm::vec3 target){
                this->target = target;
            }
            void updateSpeed(GLfloat speed){
                this->speed = speed;
            }
            void updateUp(glm::vec3 up){
                this->up = up;
            }
            void updateFront(glm::vec3 front){
                this->front = front;
            }
            void updateFront(GLfloat sensitivity){
                this->sensitivity = sensitivity;
            }
            void updateZoom(GLfloat zoom){
                this->zoom_level = zoom;
            }

            void updateAll( glm::vec3 position, glm::vec3 front , glm::vec3 target, glm::vec3 up, GLfloat speed){
                this->up = up;
                this->speed = speed;
                this->position = position;
                this->target = target;
                this->front = front;
            }

            void update(EaseWindow window, GLuint shader){
                std::copy(this->keys, this->keys+1024, sdjaskdbask::keys );
                sdjaskdbask::zoom_level = this->zoom_level;
                sdjaskdbask::position = this->position;
                sdjaskdbask::target = this->target;
                sdjaskdbask::front = this->front;
                sdjaskdbask::lastX = this->lastX;
                sdjaskdbask::lastY = this->lastY;
                sdjaskdbask::up = this->up;
                sdjaskdbask::speed = this->speed;
                sdjaskdbask::sensitivity = this->sensitivity;
                sdjaskdbask::xoffset = this->xoffset;
                sdjaskdbask::yoffset = this->yoffset;
                sdjaskdbask::pitch_mouse = this->pitch_mouse;
                sdjaskdbask::yaw_mouse = this->yaw_mouse;
                sdjaskdbask::firstMouse = this->firstMouse;

                this->view = glm::lookAt(this->position, this->target, this->up);
                this->projection = glm::perspective( glm::radians(this->zoom_level) , (float)window.getWidth()/(float)window.getHeight() , 0.1f , 100.0f );
                
                glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE , value_ptr(this->projection));  
                glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE , value_ptr(this->view));
            }




            void canMoveLegs(bool can){
                if(can){
                    addKeyCallBack(sdjaskdbask::___WASDcontrols);
                }
            }

            void moveLegs(){
                // this->speed = 3.0f*delta_time;
                if(this->keys[GLFW_KEY_W]){
                    this->position *= this->speed * this->front;
                }
                if(keys[GLFW_KEY_S]){
                    this->position *= this->speed * this->front;
                }
                if(keys[GLFW_KEY_A]){
                    this->position -= glm::normalize(glm::cross(this->front, this->up)) * this->speed;
                }
                if(keys[GLFW_KEY_D]){
                    this->position += glm::normalize(glm::cross(this->front, this->up)) * this->speed;
                }

                if(!this->fly)
                    this->position.y = 2.0f;
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