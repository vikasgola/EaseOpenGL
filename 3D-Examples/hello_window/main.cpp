
#include "../../dist/easeopengl.hpp"

#include<iostream>
using namespace std;
using namespace easeopengl;

int main(int argc, char const *argv[]){
    
    easeInit(3);
    EaseWindow3D window(800,600, "Hello Window");
    window.use();

    while(window.isOpen()){
        window.checkEvents();

        window.swapBuffers();
    }

    easeEnd();
    return 0;
}
