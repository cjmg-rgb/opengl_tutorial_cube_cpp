#version 440 core

layout (location = 0) in vec3 vs_position;  
layout (location = 1) in vec3 vs_color;                        
layout (location = 2) in vec2 vs_texcoord;                        

out vec3 fs_position;
out vec3 fs_color;
out vec2 fs_texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;




void main(){        
	fs_position = vs_position;
	fs_texcoord = vs_texcoord;      
	fs_color = vs_color;
	gl_Position = projection * view * model * vec4(vs_position, 1.f);     
}