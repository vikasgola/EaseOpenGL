#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "shape.hpp"
#include<math.h>

namespace easeopengl{
    class Polygon:public EaseShape{
        GLfloat circum_radius;
        GLfloat x,y;

        public:
            Polygon(GLfloat circum_radius, GLuint sides ,GLfloat x= 0.0f, GLfloat y = 0.0f){
                this->x = x;
                this->y = y;

                GLuint PARTITIONS = sides*2;

                this->number_of_vertices = PARTITIONS*2 + 2;
                this->number_of_indices = PARTITIONS*3;

                GLfloat vert[this->number_of_vertices];
                GLuint ind[this->number_of_indices];

                vert[0] = x;
                vert[1] = y;

                for(int i=0;i<this->number_of_vertices;i+=2){
                    vert[2+i] = x + circum_radius*sin(2.0f*M_PI*(float)i/PARTITIONS );
                    vert[i+3] = y + circum_radius*cos(2.0f*M_PI*(float)i/PARTITIONS ); 
                }

                for(int i=0;i<this->number_of_indices;i+=3){
                    ind[i] = 0;
                    ind[i+1] = 1 + (int)(i/3); 
                    ind[i+2] = 2 + (int)(i/3);
                }
                
                this->createShape(vert,ind);
            }

            void draw(EaseWindow2D window, GLuint draw_using=GL_TRIANGLES){
                EaseShape::draw(draw_using,window);
            }

    };

}

#endif