
#include "../../dist/easeopengl.hpp"

#include<iostream>
using namespace std;
using namespace easeopengl;
using namespace glm;

int main(int argc, char const *argv[]){
    
    easeInit(3);

    EaseWindow2D window(800,600,"Polygons");
    window.use();


    Circle circle(0.05f);
    vec2 v(0.01f,0.01f);
    vec2 pos(0.3f, 0.8f);
    vec2 g(0.0f, -0.001f);

    while(window.isOpen()){
        window.checkEvents();
        window.clear();

        circle.clearModel();
        circle.translate(pos.x,pos.y);
        circle.draw(window);

        if(pos.x < -1.0f + 0.05f){
            pos.x = -1.0f + 0.05f;
            v.x = -v.x;
        }
        if(pos.x > 1.0f - 0.05f){
            pos.x = 1.0f - 0.05f;
            v.x = -v.x;
        }

        if(pos.y < -1.0f + 0.05f){
            pos.y = -1.0f + 0.05f;
            v.y = -v.y/1.1f;
        }
        if(pos.y > 1.0f - 0.05f){
            pos.y = 1.0f - 0.05f;            
            v.y = -v.y;
        }
        pos = pos + v;
        v = v + g;


        window.swapBuffers();
    }

    easeEnd();
    return 0;
}
