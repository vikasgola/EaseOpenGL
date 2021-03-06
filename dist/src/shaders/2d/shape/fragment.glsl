#version 330 core

in vec2 texture_coordinates;

out vec4 color;

uniform sampler2D texture_sampler;
uniform vec3 object_color;

void main(){
    color = vec4(object_color , 1.0f) + texture(texture_sampler , texture_coordinates);
}
