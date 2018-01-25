#version 330 core

in  vec3 uv;
out vec4 frag;

uniform sampler2D tex;

void main() {
	frag=texture(tex,uv.xy);
}
