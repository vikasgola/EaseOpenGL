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
