#version 330 core

out vec4 color;

uniform sampler2D texture_sampler;

uniform vec3 object_color;

void main(){
    color = vec4(object_color , 1.0f);
}
