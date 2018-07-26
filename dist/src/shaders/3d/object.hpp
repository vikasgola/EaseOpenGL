
#ifndef OBJECT_SHADER_HPP
#define OBJECT_SHADER_HPP

namespace easeopengl{
    namespace shaders3d{
    const char* vertex_object_shader = 
R"(
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
)";

    const char* fragment_object_shader = 
R"(
#version 330 core

out vec4 color;

in vec4 vertex_color;
in vec2 texture_coordinates;
in vec3 normal;
in vec3 fragment_position;


struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

uniform sampler2D texture_sampler;
uniform vec3 camera_position;

void main(){

    // ambient light
    float ambientStrength = 0.3f;
    vec3 ambient = light.ambient * material.ambient;

    // diffuse light
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light.position-fragment_position);
    float diff = max(dot(norm,light_dir),0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // specular light
    float specularStrength = 0.5f;
    vec3 view_dir = normalize(camera_position - fragment_position);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);


    vec3 result_color = ambient + diffuse + specular;
    
    color = vec4(result_color , 1.0f) + vertex_color + texture(texture_sampler , texture_coordinates);
}

)";
    }
}

#endif