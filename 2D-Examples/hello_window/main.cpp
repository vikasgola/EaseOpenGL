
#include "../../dist/2d/easeopengl2d.hpp"

#include<iostream>

using namespace std;
using namespace easeopengl2d;

int main(int argc, char const *argv[]){
    
    init(3);

    EaseWindow2D window(800,600, "Hello Window");

    window.use();

    while(window.isOpen()){
        window.checkEvents();

        window.swapBuffers();
    }

    end();
    return 0;
}
