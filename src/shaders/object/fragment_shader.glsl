#version 330 core

out vec4 color;

in vec4 vertex_color;
in vec2 texture_coordinates;
in vec3 normal;
in vec3 fragment_position;

uniform sampler2D texture_sampler;

// uniforms are global
uniform vec3 object_color;

uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 camera_position;

void main(){

    // ambient light
    float ambientStrength = 0.3f;
    vec3 ambient = ambientStrength * light_color;

    // diffuse light
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_position-fragment_position);
    float diff = max(dot(norm,light_dir),0.0);
    vec3 diffuse = diff * light_color;

    // specular light
    float specularStrength = 0.5f;
    vec3 view_dir = normalize(camera_position - fragment_position);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = specularStrength * spec * light_color;


    vec3 result_color = (ambient + diffuse + specular) * object_color;
    
    color = vec4(result_color , 1.0f) + vertex_color + texture(texture_sampler , texture_coordinates);
}
