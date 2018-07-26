
#ifndef VBO_HPP
#define VBO_HPP

namespace easeopengl{

    template<class Data>
    class VBO{
        GLuint vbo;
        Data *vbo_data;
        GLuint vbo_data_length;

        public:
            GLuint getVBO(){
                return this->vbo;
            }

            Data getVBOData(){
                return this->vbo_data;
            }

            VBO(Data data[] , GLuint data_length){
                this->vbo_data = data;
                this->vbo_data_length = data_length;

                glGenBuffers(1, &this->vbo);
                glBindBuffer(GL_ARRAY_BUFFER,this->vbo);

                glBufferData(GL_ARRAY_BUFFER, this->vbo_data_length*sizeof(this->vbo_data), this->vbo_data, GL_STATIC_DRAW);
            }

            void setVertexAttrib(GLuint location, GLuint size, GLuint offset, GLuint point_length=3){
                glVertexAttribPointer(location , size , GL_FLOAT , GL_FALSE, point_length*sizeof(Data), (GLvoid*)(offset * sizeof(Data)));
                glEnableVertexAttribArray(location);
            }

            void unbind(){
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

    };
}
#endif