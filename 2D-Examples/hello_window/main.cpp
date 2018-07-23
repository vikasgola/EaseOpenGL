
#include "../lib/easeopengl2d.hpp"

#include<iostream>

using namespace std;
using namespace easeopengl2d;

int main(int argc, char const *argv[]){
    
    init(3);

    EaseWindow2D window(800,600, "Hello Window");

    window.use();

    while(window.isOpen()){
        glfwPollEvents();

        glfwSwapBuffers(window.getWindow());
    }

    end();
    return 0;
}
