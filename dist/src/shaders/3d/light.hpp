
#ifndef LIGHT_SHADER_HPP
#define LIGHT_SHADER_HPP

namespace easeopengl{
    namespace shaders3d{
    const char* vertex_light_shader = 
R"(
#version 330 core

layout (location = 0 ) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position =  projection * view* model *vec4(position , 1.0);

})";

    const char* fragment_light_shader = 
R"(
#version 330 core

out vec4 color;

uniform sampler2D texture_sampler;

uniform vec3 object_color;

void main(){
    color = vec4(object_color , 1.0f);
}
)";
    }
}

#endif