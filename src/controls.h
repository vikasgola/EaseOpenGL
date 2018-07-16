
#ifndef CONTROLS_H
#define CONTROLS_H

#include<vector>

namespace easeopengl{
    std::vector< void (*)(GLFWwindow* , int , int , int , int)> keyfunctions;
    std::vector< void (*)(GLFWwindow* , double ,double)> mousefunctions;
    std::vector< void (*)(GLFWwindow* , double , double)> scrollfunctions;
    
    void addKeyCallBack(void (*keyfunction)(GLFWwindow* , int , int , int , int)){
        keyfunctions.push_back(keyfunction);
    }

    void addMouseCallBack(void (*mousefunction)(GLFWwindow* , double ,double)){
        mousefunctions.push_back(mousefunction);
    }

    void addScrollCallBack(void (*scrollfunction)(GLFWwindow* , double ,double)){
        scrollfunctions.push_back(scrollfunction);
    }

    void ___key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
        for(int i=0;i<keyfunctions.size();i++){
            keyfunctions[i](window,key,scancode,action,mode);
        }
    }

    void ___mouse_callback(GLFWwindow* window, double xpos, double ypos){
        for(int i=0;i<mousefunctions.size();i++){
            mousefunctions[i](window,xpos,ypos);
        }
    }
    void ___scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
        for(int i=0;i<scrollfunctions.size();i++){
            scrollfunctions[i](window,xoffset,yoffset);
        }
    }
}


#endif