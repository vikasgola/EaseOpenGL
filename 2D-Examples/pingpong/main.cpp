
#include "../../dist/easeopengl.hpp"

#include<iostream>
using namespace std;
using namespace easeopengl;
using namespace glm;


GLfloat y = 0.0f;
GLfloat y2 = 0.0f;
bool keys[1024];

void keyboard(GLFWwindow *window,int key, int scancode, int action, int mode){
    if(action == GLFW_PRESS){
        keys[key] = true;
    }else if(action == GLFW_RELEASE){
        keys[key] = false;
    }
}
void keyControl(Rectangle bat1, Rectangle bat2,EaseWindow2D window){

    if(keys[GLFW_KEY_Q]){
        y += 0.02f;
    }
    if(keys[GLFW_KEY_A]){
        y -= 0.02f;
    }
    if(keys[GLFW_KEY_P]){
        y2 += 0.02f;
    }
    if(keys[GLFW_KEY_L]){
        y2 -= 0.02f;
    }
}

int main(int argc, char const *argv[]){
    
    easeInit(3);

    EaseWindow2D window(800,600,"Polygons");
    window.use();

    Circle circle(0.02f);
    Rectangle bat1(0.03f,1.0f);
    Rectangle bat2(0.03f,1.0f);


    addKeyCallBack(keyboard);

    vec2 v(0.02f,-0.01f);
    vec2 pos(0.0f, 0.0f);

    while(window.isOpen()){
        window.checkEvents();
        window.clear();

        circle.clearModel();
        circle.setPosition(pos.x,pos.y);
        circle.draw(window);


        keyControl(bat1,bat2,window);
        
        bat1.clearModel();
        bat2.clearModel();
        bat1.setPosition(-1.0f + 0.03f, y);
        bat1.draw(window);
        bat2.setPosition(1.0f - 0.03f, y2);
        bat2.draw(window);
        

        vec3 a = bat1.getPosition();
        vec3 b = bat2.getPosition();

        if(pos.x > a.x - 0.015f && pos.x - 0.02f < a.x + 0.015f && pos.y < a.y + 0.5f && pos.y > a.y - 0.5f){
            v.x = -v.x;

            if(keys[GLFW_KEY_Q])
                v.y = v.y + 0.001;
            else if(keys[GLFW_KEY_A])
                v.y = v.y - 0.001;

            pos.x = a.x + 0.015f;
        }
        
        if(pos.x > b.x - 0.015f && pos.x - 0.02f < b.x + 0.015f && pos.y < b.y + 0.5f && pos.y > b.y - 0.5f){
            v.x = -v.x;
            
            if(keys[GLFW_KEY_P])
                v.y = v.y + 0.001;
            else if(keys[GLFW_KEY_L])
                v.y = v.y - 0.001;

            pos.x = b.x - 0.015f;
        }

        if(pos.y < -1.0f + 0.05f){
            pos.y = -1.0f + 0.05f;
            v.y = -v.y;
        }
        if(pos.y > 1.0f - 0.05f){
            pos.y = 1.0f - 0.05f;            
            v.y = -v.y;
        }
        pos = pos + v;


        window.swapBuffers();
    }

    easeEnd();
    return 0;
}
