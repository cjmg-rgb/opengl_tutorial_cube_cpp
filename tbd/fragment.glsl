#version 440 core                      

in vec3 fs_color;                        
in vec3 fs_position;
in vec2 fs_texcoord;

out vec4 FragColor;  

uniform sampler2D texture0;

void main(){                                
	FragColor = texture(texture0, fs_texcoord);            
}
