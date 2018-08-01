
#ifndef OBJECT_SHADER_HPP
#define OBJECT_SHADER_HPP

namespace easeopengl{
    namespace shaders3d{
    const char* vertex_object_shader = 
R"(
#version 330 core

layout (location = 0 ) in vec3 position;
layout ( location = 1 ) in vec3 normal_cord;
layout ( location = 2 ) in vec2 texture_cord;

out vec2 texture_coordinates;
out vec3 normal;
out vec3 fragment_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position =  projection * view* model *vec4(position , 1.0);
    fragment_position = vec3(model*vec4(position, 1.0f));
    texture_coordinates = texture_cord;
    normal = mat3(transpose(inverse(model)))*normal_cord;
}

)";

    const char* fragment_object_shader = 
R"(
#version 330 core

out vec4 color;

in vec2 texture_coordinates;
in vec3 normal;
in vec3 fragment_position;


struct ColorMaterial{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    bool isUsing;
};

struct TexturedMaterial{
    sampler2D diffuse;
    sampler2D specular;
    
    vec3 specularD;
    float shininess;

    bool isUsing;
    bool haveSpecular;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    bool isDirectional;
};

uniform ColorMaterial cmaterial;
uniform TexturedMaterial tmaterial;
uniform Light light;

uniform vec3 camera_position;

void main(){
    vec3 ambient,diffuse,specular;

    vec3 norm = normalize(normal);
    vec3 light_dir;

    if(!light.isDirectional)
        light_dir = normalize(light.position-fragment_position);
    else
        light_dir = normalize(-light.position);

    float diff = max(dot(norm,light_dir),0.0);

    vec3 view_dir = normalize(camera_position - fragment_position);
    vec3 reflect_dir = reflect(-light_dir, norm);

    if(cmaterial.isUsing){
        // ambient light
        ambient = light.ambient * cmaterial.ambient;
        // diffuse light
        diffuse = light.diffuse * (diff * cmaterial.diffuse);
        // specular light
        float spec = pow(max(dot(view_dir, reflect_dir), 0.0), cmaterial.shininess);
        specular = light.specular * (spec * cmaterial.specular);

    }else if(tmaterial.isUsing){
        ambient = light.ambient * vec3(texture(tmaterial.diffuse, texture_coordinates));

        diffuse = light.diffuse * diff * vec3(texture(tmaterial.diffuse,texture_coordinates));

        // specular light
        float spec = pow(max(dot(view_dir, reflect_dir), 0.0), tmaterial.shininess);
        if(!tmaterial.haveSpecular){
            specular = light.specular * (spec * tmaterial.specularD);
        }else{
            specular = light.specular * spec * vec3(texture(tmaterial.specular,texture_coordinates));
        }
    }
    
    color = vec4(ambient + diffuse + specular , 1.0f);
}


)";
    }
}

#endif