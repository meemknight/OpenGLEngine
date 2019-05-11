#version 400

in layout(location = 0)vec4 vertex;
in layout(location = 1)vec4 position;
in layout(location = 2)vec4 inColor;

out vec4 color;
uniform mat4 projectionMatrix;

void main()
{
	color = inColor;

	//mat4 modelMatrix = mat4(1.0, 0.0, 0.0, 0.0, 
	//						0.0, 1.0, 0.0, 6.0, 
	//						0.0, 0.0, 1.0, 0.0,  
	//						0.0, 0.0, 0.0, 1.0);
	//
	//modelMatrix[0][1] = projectionMatrix[1][0];
	//modelMatrix[0][2] = projectionMatrix[2][0];
	//modelMatrix[2][1] = projectionMatrix[1][2];
	//modelMatrix[1][0] = projectionMatrix[0][1];
	//modelMatrix[2][0] = projectionMatrix[0][2];
	//modelMatrix[1][2] = projectionMatrix[2][1];
	//modelMatrix[0][0] = projectionMatrix[0][0];
	//modelMatrix[1][1] = projectionMatrix[1][1];
	//modelMatrix[2][2] = projectionMatrix[2][2];
	//
	vec4 newPos = vertex + position;
	
	gl_Position = projectionMatrix * newPos;
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