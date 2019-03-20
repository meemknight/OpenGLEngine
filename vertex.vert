#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 incolor;
layout (location = 2) in mat4 u_full;
layout (location = 6) in mat4 objectToWorld;
out vec3 color;

//uniform mat4 u_full;
uniform float u_time;
uniform vec3 u_ambience;
uniform float u_c;

void main()
{
	vec4 finalPosition;
	
	finalPosition = u_full * vec4(position.xyz, 1.0);

	gl_Position = finalPosition;
	
	color = incolor;
}