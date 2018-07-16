# EaseOpenGL
Library that makes **Modern** openGL easy to use.

## prerequisite
1. opengl library
2. soil library
3. glfw
4. glew
5. glm
6. c++11 compiler

## How to use
Open terminal in linux and follow commands
1. clone the library in your working directory
  ```git clone https://github.com/vikasgola/EaseOpenGL```
2. include easeopengl.h in your program
```#include "easeopengl.h"```

## Hello Window
```
// include easeopengl
#include "easeopengl.h"

// main function
int main(int argc, char const *argv[]){

    // specify opengl version in init. Here we are using version 3
    easeopengl::init(3);
    // creating a window of width 800 and height 600 with title "EaseOpenGL"
    GLFWwindow* window = easeopengl::createWindow(800,600,"EaseOpenGL");
    // use that window 
    easeopengl::useWindow(window);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();        
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}
```
This is just hello window in EaseOpenGL. It can do much more.

## Docs
**Coming soon!!!**