#version 330 core

in  vec3 pos;
out vec2 uv;

uniform mat4 PVM;

void main() {
	gl_Position=PVM * vec4(pos,1.0);
	uv=pos.xy;
}
