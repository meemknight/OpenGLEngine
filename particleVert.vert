#version 400

in layout(location = 0)vec4 vertex;
in layout(location = 1)vec4 position;
in layout(location = 2)vec4 inColor;

out vec4 color;
uniform mat4 projectionMatrix;
uniform mat4 positionMatrix;

uniform int count;
uniform int firstPos;

void main()
{

	float c = (float(gl_InstanceID) - firstPos) / float(count);
	 c += int(c < 0);
	color = vec4(c,c,c,1) * inColor;

	mat4 translationMatrix = mat4(1.0, 0.0, 0.0, position.x, 
							0.0, 1.0, 0.0, position.y, 
							0.0, 0.0, 1.0, position.z,  
							0.0, 0.0, 0.0, 1.0);

							translationMatrix = transpose(translationMatrix);

	mat4 modelView = positionMatrix * translationMatrix;

	modelView[0][0] = 1;
	modelView[1][1] = 1;
	modelView[2][2] = 1;
	modelView[0][1] = 0;
	modelView[1][0] = 0;
	modelView[0][2] = 0;
	modelView[2][0] = 0;
	modelView[2][1] = 0;
	modelView[1][2] = 0;
	

	gl_Position = projectionMatrix * modelView * vertex;
}

/*	projection[0][1] = 0.f;
	projection[1][0] = 0.f;
	projection[0][2] = 0.f;
	projection[2][0] = 0.f;
	projection[1][2] = 0.f;
	projection[2][1] = 0.f;

	projection[0][0] = 1.f;
	projection[1][1] = 1.f;
	projection[2][2] = 1.f;
*/