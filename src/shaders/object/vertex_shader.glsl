#version 330 core

layout (location = 0 ) in vec3 position;
layout (location = 1 ) in vec3 input_color;
layout ( location = 2 ) in vec2 texture_cord;
layout ( location = 3 ) in vec3 normal_cord;

out vec4 vertex_color;
out vec2 texture_coordinates;
out vec3 normal;
out vec3 fragment_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position =  projection * view* model *vec4(position , 1.0);
    fragment_position = vec3(model*vec4(position, 1.0f));
    vertex_color = vec4(input_color , 1.0f);
    texture_coordinates = texture_cord;
    normal = mat3(transpose(inverse(model)))*normal_cord;
}
