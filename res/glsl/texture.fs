#version 330

in vec2 uv;
in vec2 vUV;

uniform sampler2D tex;
uniform sampler2D tex2;

out vec4 gl_FragColor;

void main () {
	gl_FragColor = vec4(texture( tex, vUV ).rgb, 1.0);
}