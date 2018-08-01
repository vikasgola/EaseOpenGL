#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "polygon.hpp"
#include<math.h>

namespace easeopengl{
    class Circle:public Polygon{
        public:
            Circle(GLfloat radius, GLfloat x=0.0f, GLfloat y=0.0f):Polygon(radius,180,x,y){};
    };
}

#endif