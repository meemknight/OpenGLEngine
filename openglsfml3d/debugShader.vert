#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 incolor;
out vec3 color;
uniform mat4 u_full;

void main()
{
	vec4 finalPosition;
	
	finalPosition = u_full * vec4(position.xyz, 1.0);

	gl_Position = finalPosition;
	
	color = incolor;
}