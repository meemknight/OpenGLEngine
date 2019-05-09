#version 400

in layout(location = 0)vec4 vertex;
in layout(location = 1)vec4 position;
in layout(location = 2)vec4 inColor;

out vec4 color;
uniform mat4 projectionMatrix;


void main()
{
	color = inColor;

	mat4 translationMatrix = mat4(1.0, 0.0, 0.0, 0.0, 
								  0.0, 1.0, 0.0, 6.0, 
								  0.0, 0.0, 1.0, 0.0,  
								  0.0, 0.0, 0.0, 1.0);


	mat4 modelWorldMatrix = projectionMatrix ;
	//modelWorldMatrix[1][0] = 0.f;
	//modelWorldMatrix[0][2] = 0.f;
	//modelWorldMatrix[0][1] = 0.f;
	//modelWorldMatrix[2][0] = 0.f;
	//modelWorldMatrix[1][2] = 0.f;
	//modelWorldMatrix[2][1] = 0.f;
	//
	//modelWorldMatrix[0][0] = 1.f;
	//modelWorldMatrix[1][1] = 1.f;
	//modelWorldMatrix[2][2] = 1.f;
	
	gl_Position = modelWorldMatrix * vertex;
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