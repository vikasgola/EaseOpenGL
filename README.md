# EaseOpenGL
Library that makes **Modern** openGL easy to use.

## prerequisite
1. c++11 compiler
2. soil
3. glfw
4. glew
5. glm

## How to use
Open terminal in linux and follow commands
1. clone the library in your working directory
  ```git clone https://github.com/vikasgola/EaseOpenGL```
2. include easeopengl.h in your program
```#include "easeopengl.h"```

## Hello Window
```
// include easeopengl
#include "easeopengl.hpp"

#include<iostream>
using namespace std;
using namespace easeopengl;

int main(int argc, char const *argv[]){
    
    easeInit(3);
    EaseWindow3D/EaseWindow2D window(800,600, "Hello Window");
    window.use();

    while(window.isOpen()){
        window.checkEvents();

        window.swapBuffers();
    }

    easeEnd();
    return 0;
}
```

## Docs
**Coming soon!!!**