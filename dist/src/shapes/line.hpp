#ifndef LINE_HPP
#define LINE_HPP

#include "shape.hpp"
#include<math.h>

namespace easeopengl{
    class Line:public EaseShape{
        GLfloat x,y,x2,y2;

        public:
            Line(GLfloat x, GLfloat y,GLfloat x2, GLfloat y2){
                this->x = x;
                this->y = y;
                this->x2 = x2;
                this->y2 = y2;
                GLfloat vert[4] = {x,y,x2,y2};

                this->number_of_vertices = 4;
                this->createShape(vert);
            }

            void draw(EaseWindow2D window){
                EaseShape::draw(GL_LINES,window);
            }
    };
}

#endif