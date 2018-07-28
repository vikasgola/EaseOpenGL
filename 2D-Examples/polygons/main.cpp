
#include "../../dist/easeopengl.hpp"

#include<iostream>
using namespace std;
using namespace easeopengl;

int main(int argc, char const *argv[]){
    
    easeInit(3);

    EaseWindow2D window(800,600,"Polygons");
    window.use();


    Circle circle(0.2f ,-0.5f, -0.5f);
    
    Rectangle rect(0.2f,0.4f, -0.5f,0.5f);
    Rectangle square(0.2f,0.2f, 0.5f,0.5f);

    Polygon triangle(0.2f,3);
    Polygon pentagon(0.2f,5,0.5f,-0.5f);

    Point a(0.0f,-1.0f);

    while(window.isOpen()){
        window.checkEvents();

        window.clear();

        circle.draw(window);

        rect.draw(window);
        square.draw(window);
        triangle.draw(window);
        pentagon.draw(window);

        window.swapBuffers();
    }

    easeEnd();
    return 0;
}
