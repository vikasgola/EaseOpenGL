
#ifndef EBO_H
#define EBO_H

namespace easeopengl{

    template<class Data>
    class EBO{
        
        GLuint ebo;
        Data *ebo_data;
        GLuint ebo_data_length;

        public:
            GLuint getEBO(){
                return this->ebo;
            }

            Data getEBOData(){
                return this->ebo_data;
            }
            
            EBO(Data data[] , GLuint data_length){
                this->ebo_data = data;
                this->ebo_data_length = data_length;

                glGenBuffers(1, &this->ebo);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->ebo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->ebo_data_length*sizeof(this->ebo_data), this->ebo_data, GL_STATIC_DRAW);
            }

            void unbind(){
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
    };
}
#endif