#version 400

in vec3 color;

void main()
{
	vec4 c = vec4(color.xyz ,1);

	gl_FragColor = c;
		
}