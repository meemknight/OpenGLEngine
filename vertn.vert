#version 330

layout (location = 0) in vec4 position; //vec3 (var var var) 1.0
layout (location = 1) in vec3 incolor;
layout (location = 2) in vec3 normals;
layout (location = 3) in mat4 u_full;
layout (location = 7) in mat4 modelToWorld;

out vec3 color;
out vec3 outNormal;
out vec3 worldspace;


//uniform mat4 u_full;
uniform float u_time;
uniform vec3 u_ambience;
uniform vec4 u_lightPosition;
uniform vec3 u_eyePosition;

void main()
{
	vec4 finalPosition;
	
	finalPosition = u_full * position;

	color = incolor;
	outNormal = vec3(modelToWorld * vec4(normals,0)); //niormalise ?? 
	
	gl_Position = finalPosition;
	worldspace = (modelToWorld * position).xyz;
}