#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "polygon.hpp"

#include<math.h>

namespace easeopengl{

    class Rectangle:public EaseShape{
        GLfloat x,y;
        GLfloat width,height;

        public:
            Rectangle(GLfloat width, GLfloat height, GLfloat x=0.0f, GLfloat y=0.0f){
                this->x= x;
                this->y = y;
                this->width =width;
                this->height = height;

                this->number_of_vertices = 12;

                GLfloat points[12] = {
                    x - (float)width/2, y + (float)height/2,
                    x + (float)width/2, y + (float)height/2,
                    x - (float)width/2, y - (float)height/2,

                    x + (float)width/2, y + (float)height/2,
                    x - (float)width/2, y - (float)height/2,
                    x + (float)width/2, y - (float)height/2
                };

                this->createShape(points);
            }

            void draw(EaseWindow2D window, GLuint draw_using=GL_TRIANGLES){
                EaseShape::draw(draw_using,window);
            }
    };
}

#endif