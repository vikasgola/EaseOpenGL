
#ifndef CONTROLS_H
#define CONTROLS_H

#include<vector>

namespace easeopengl{
    std::vector< void (*)(GLFWwindow* , int , int , int , int)> ease_keyfunctions;
    std::vector< void (*)(GLFWwindow* , double ,double)> ease_mousefunctions;
    std::vector< void (*)(GLFWwindow* , double , double)> ease_scrollfunctions;
    
    void addKeyCallBack(void (*keyfunction)(GLFWwindow* , int , int , int , int)){
        ease_keyfunctions.push_back(keyfunction);
    }

    void addMouseCallBack(void (*mousefunction)(GLFWwindow* , double ,double)){
        ease_mousefunctions.push_back(mousefunction);
    }

    void addScrollCallBack(void (*scrollfunction)(GLFWwindow* , double ,double)){
        ease_scrollfunctions.push_back(scrollfunction);
    }

    void ___key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
        for(int i=0;i<ease_keyfunctions.size();i++){
            ease_keyfunctions[i](window,key,scancode,action,mode);
        }
    }

    void ___mouse_callback(GLFWwindow* window, double xpos, double ypos){
        for(int i=0;i<ease_mousefunctions.size();i++){
            ease_mousefunctions[i](window,xpos,ypos);
        }
    }
    void ___scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
        for(int i=0;i<ease_scrollfunctions.size();i++){
            ease_scrollfunctions[i](window,xoffset,yoffset);
        }
    }
}


#endif