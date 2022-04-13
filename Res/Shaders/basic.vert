// Request GLSL3.3
#version 330

in vec3 inPosition;

void main(){
	gl_position = vec4(inPosition,1.0);
}