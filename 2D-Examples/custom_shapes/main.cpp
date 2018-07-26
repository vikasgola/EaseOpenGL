
#include "../../dist/easeopengl.hpp"

#include<iostream>
using namespace std;
using namespace easeopengl;

GLfloat triangle_vert[] = {
    0.5f, 0.0f,
    0.0f , 0.5f,
    -0.5f, 0.0f,
};

int main(int argc, char const *argv[]){
    
    easeInit(3);

    EaseWindow2D window(800,600,"Hello Window");
    window.use();

    EaseShape triangle(triangle_vert,6);

    // triangle.setScale(0.2f,0.2f);

    while(window.isOpen()){
        window.checkEvents();

        window.clear();

        // triangle.clearModel();
        triangle.setRotation(00.004f);
        triangle.setColor(sin(glfwGetTime()) ,sin(glfwGetTime() + 10) ,sin(glfwGetTime())+ 20);
        triangle.draw(GL_TRIANGLE_FAN,window);

        window.swapBuffers();
    }

    easeEnd();
    return 0;
}
