#version 460 core
out vec4 FragColor;
in vec2 TexCoord;
in float Height;
in float Energy;

void main() {
    vec3 color = vec3(0.1, 0.1, 0.2); 
    color += vec3(0.0, 0.5, 1.0) * Height * 2.0; 
    color += vec3(1.0, 0.2, 0.5) * Energy; 

    FragColor = vec4(color, 1.0);
}