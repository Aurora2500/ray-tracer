#version 330 core
layout(location = 0) out vec4 color;
in vec2 uv;

uniform sampler2D my_tex;

void main(){
	color = vec4(texture(my_tex, uv).xyz, 1.0);
}