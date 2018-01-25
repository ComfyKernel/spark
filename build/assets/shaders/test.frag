#version 330 core

in  vec3 uv;
out vec4 frag;

void main() {
	frag=vec4(uv,1.0); }
