
#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include<vector>

namespace easeopengl{
    namespace __hidden{
        std::vector< void (*)(GLFWwindow* , int , int , int , int)> ease_keyfunctions;
        std::vector< void (*)(GLFWwindow* , double ,double)> ease_mousefunctions;
        std::vector< void (*)(GLFWwindow* , double , double)> ease_scrollfunctions;
    }

    void addKeyCallBack(void (*keyfunction)(GLFWwindow* , int , int , int , int)){
        __hidden::ease_keyfunctions.push_back(keyfunction);
    }

    void addMouseCallBack(void (*mousefunction)(GLFWwindow* , double ,double)){
        __hidden::ease_mousefunctions.push_back(mousefunction);
    }

    void addScrollCallBack(void (*scrollfunction)(GLFWwindow* , double ,double)){
        __hidden::ease_scrollfunctions.push_back(scrollfunction);
    }

    void ___key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
        for(int i=0;i<__hidden::ease_keyfunctions.size();i++){
            __hidden::ease_keyfunctions[i](window,key,scancode,action,mode);
        }
    }

    void ___mouse_callback(GLFWwindow* window, double xpos, double ypos){
        for(int i=0;i<__hidden::ease_mousefunctions.size();i++){
            __hidden::ease_mousefunctions[i](window,xpos,ypos);
        }
    }
    void ___scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
        for(int i=0;i<__hidden::ease_scrollfunctions.size();i++){
            __hidden::ease_scrollfunctions[i](window,xoffset,yoffset);
        }
    }
}


#endif