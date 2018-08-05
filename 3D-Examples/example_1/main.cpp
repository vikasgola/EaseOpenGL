#include "../../dist/easeopengl.hpp"

#include<math.h>

using namespace std;
using namespace glm;
using namespace easeopengl;


// global variables
GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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

    EaseObject cube(8, 012 , vertices, sizeof(vertices)/sizeof(vertices[0]),vec3(1.0f,1.0f,1.0f));
    EaseObject plane(6 ,01 ,plane_vertices,36, vec3(0.3f,0.1f,0.4f));
    plane.scale(4.0f,4.0f,4.0f);

    cube.addTexture("container2.png","container2_specular.png");
    window.captureMouse();

    Camera camera(window);
    camera.setPosition(vec3(0.0f,0.0f,22.0f));
    camera.setHeight(5.0f);
    camera.canMoveLegs(true);
    camera.canMoveHead(true);

    // Light light(vec3(1.0f,1.0f,1.0f),vec3(1.0f,3.0f,-2.0f));

    SpotLight light(vec3(1.0f,1.0f,1.0f),vec3(0.0f,8.0f,0.0f),vec3(0.0f,-1.0f,0.0f),12.0f);

    // PointLight light(vec3(1.0f,1.0f,1.0f),vec3(1.0f,3.0f,-2.0f),vec3(1.0f,0.03f,0.01f));

    // DirectionalLight light1(vec3(1.0f,1.0f,1.0f),vec3(-0.2f, -1.0f, -0.3f));


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

        // light.clearModel();
        // light.setProperties(vec3(0.2f),vec3(sin(glfwGetTime()*0.1f),sin(glfwGetTime()*0.3f),sin(glfwGetTime()*0.78)),vec3(1.0f),window);
        // light.setPosition(vec3(radi_x, 4.0f , radi_z),window);
        light.on(window);
        // light.show(window);

        
        cube.clearModel();
        cube.translate(vec3(0.0f,0.5f,0.0f));
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
