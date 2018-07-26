#include "../../dist/easeopengl.hpp"

#include<math.h>

using namespace std;
using namespace glm;
using namespace easeopengl;


// global variables
GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

GLfloat plane_vertices[] = {
    -10.0f, 0.0f , -10.0f, 0.0f , 1.0f , 0.0f,
    10.0f,  0.0f , -10.0f, 0.0f , 1.0f , 0.0f,
    10.0f,  0.0f , 10.0f, 0.0f , 1.0f , 0.0f,

    10.0f,   0.0f , 10.0f, 0.0f , 1.0f , 0.0f,
    -10.0f,  0.0f , -10.0f, 0.0f , 1.0f , 0.0f,
    -10.0f,  0.0f , 10.0f ,  0.0f , 1.0f , 0.0f,
};


// drawing staff
void draw(EaseWindow3D window){

    EaseObject cube(6, 03 , vertices,216 , vec3(0.4f,0.6f,0.8f));
    EaseObject plane(6 , 03,plane_vertices,36, vec3(0.3f,0.1f,0.4f));

    Camera camera(window);
    camera.setPosition(vec3(0.0f,0.0f,22.0f));
    camera.setHeight(5.0f);
    camera.canMoveLegs(true);
    camera.canMoveHead(true);

    Light light(vec3(1.0f,1.0f,1.0f),vec3(1.0f,3.0f,-2.0f));


    while(window.isOpen()){
        // checking for events
        window.checkEvents();

        // clearing the window
        // window.clearColor(0.5f, 0.8f, 1.0f, 1.0f);
        window.clear();

        GLfloat time_val = glfwGetTime()*30;
        GLfloat radi_x = sin(radians(time_val))*5.0f;
        GLfloat radi_z = cos(radians(time_val))*5.0f;

        camera.setTarget(camera.getPosition() + camera.getFront());
        camera.update(window);
        camera.moveLegs();

        light.clearModel();
        light.setProperties(vec3(0.2f),vec3(sin(glfwGetTime()*0.1f),sin(glfwGetTime()*0.3f),sin(glfwGetTime()*0.78)),vec3(1.0f),window);
        light.setPosition(vec3(radi_x, 4.0f , radi_z),window);
        light.on(window);
        light.show(window);

        cube.clearModel();
        cube.setPosition(vec3(0.0f,0.5f,0.0f));
        cube.draw(GL_TRIANGLES,window);

        plane.draw(GL_TRIANGLES,window);


        window.swapBuffers();
    }
}

// main function
int main(int argc, char const *argv[]){
    
    easeInit(3);
    EaseWindow3D window(800,600,"EaseOpenGL");
    window.use();
    
    draw(window);

    easeEnd();
    return 0;
}
