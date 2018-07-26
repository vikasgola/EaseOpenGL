
#ifndef SHAPE_SHADER_HPP
#define SHAPE_SHADER_HPP

namespace easeopengl{
    namespace shaders2d{
    const char* vertex_shape_shader = 
R"(
#version 330 core

layout (location = 0 ) in vec2 position;
layout ( location = 2 ) in vec2 texture_cord;

out vec2 texture_coordinates;
uniform mat4 model;

void main(){
    gl_Position = model*vec4(position,0.0f , 1.0);
    texture_coordinates = texture_cord;
}
)";

    const char* fragment_shape_shader = 
R"(
#version 330 core

in vec2 texture_coordinates;
out vec4 color;

uniform sampler2D texture_sampler;
uniform vec3 object_color;

void main(){
    color = vec4(object_color , 1.0f) + texture(texture_sampler , texture_coordinates);
}

)";
    }
}

#endif