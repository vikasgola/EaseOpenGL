#version 330 core

layout (location = 0 ) in vec3 position;
layout ( location = 2 ) in vec2 texture_cord;

out vec2 texture_coordinates;

void main(){
    gl_Position = vec4(position , 1.0);
    texture_coordinates = texture_cord;
}
