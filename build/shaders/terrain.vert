#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 view;
uniform mat4 projection;
uniform sampler2D physicsMap;
uniform sampler2D quantumMap;

out vec2 TexCoord;
out float Height;
out float Energy;

void main() {
    TexCoord = aTexCoord;
    
    float phys = texture(physicsMap, aTexCoord).r;
    float quant = texture(quantumMap, aTexCoord).b;
    
    vec3 pos = aPos;
    pos.y = phys * 0.1 + quant * 0.2; 

    Height = pos.y;
    Energy = quant;

    gl_Position = projection * view * vec4(pos, 1.0);
}