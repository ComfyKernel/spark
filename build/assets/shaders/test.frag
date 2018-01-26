#version 330 core

in  vec3 uv;
out vec4 frag;

uniform sampler2D tex;

void main() {
	frag=vec4(texture(tex,uv.xy).xyz, 1.0);
}
