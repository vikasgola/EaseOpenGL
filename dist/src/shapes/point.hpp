#ifndef POINT_HPP
#define POINT_HPP

#include "shape.hpp"
#include<math.h>

namespace easeopengl{
    class Point:public EaseShape{
        GLfloat x,y,size;

        public:
            Point(GLfloat x, GLfloat y, GLfloat size = 1.0f){
                this->x = x;
                this->y = y;
                this->size = size;
                GLfloat vert[2] = {x,y};
                this->number_of_vertices = 2;
                this->createShape(vert);
            }

            glm::vec2 getPosition(){
                return glm::vec2(this->x,this->y);
            }

            void draw(EaseWindow2D window){
                EaseShape::draw(GL_POINTS,window);
            }
    };

}

#endif