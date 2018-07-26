
#ifndef TEXTURE_H
#define TEXTURE_H

#include<SOIL/SOIL.h>

namespace easeopengl{

    class Texture{
        GLuint texture;
        const char* texture_filename;
        int texture_width, texture_height;
        unsigned char* image;

        public:
            Texture(const char* filename){
                glGenTextures(1 , &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                this->texture_filename = filename;
                this->image = SOIL_load_image(this->texture_filename ,&this->texture_width,&this->texture_height,0,SOIL_LOAD_RGB);
            }

            void generate(){
                glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGB , this->texture_width, this->texture_height, 0, GL_RGB,
                    GL_UNSIGNED_BYTE, this->image);
                glGenerateMipmap(GL_TEXTURE_2D);
                SOIL_free_image_data(this->image);
                glBindTexture(GL_TEXTURE_2D,0);
            }

            void use(EaseWindow3D window){
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture);
                glUniform1i(glGetUniformLocation(window.getObjectShader(), "texture_sampler"),0);

            }

            ~Texture(){
            }

            GLuint getTexture(){
                return this->texture;
            }

            int getTextureWidth(){
                return this->texture_width;
            }

            int getTextureHeight(){
                return this->texture_height;
            }

    };
}
#endif