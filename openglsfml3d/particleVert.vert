#version 400
#define LIGHT_COUNT 32

in layout(location = 0)vec4 vertex;
in layout(location = 1)vec4 position;
in layout(location = 2)vec4 inColor;

out vec4 color;
uniform mat4 projectionMatrix;
uniform mat4 positionMatrix;

uniform int count;
uniform int firstPos;
uniform vec3 u_fadeColor;

uniform vec4 u_lightPosition[LIGHT_COUNT]; // last component determins if it is a directional light or not, 1 means positional // ???
uniform vec3 u_lightAmbient[LIGHT_COUNT];
uniform vec3 u_lightDiffuse[LIGHT_COUNT];
uniform vec3 u_lightSpecular[LIGHT_COUNT];
uniform float u_lightStrength[LIGHT_COUNT]; //used to determine the distance to shine,   0 means infinite distance
uniform int u_lightCount;

uniform float u_fadeWeight;
uniform float u_scale = 1.f;
uniform float u_kd = 1.f;


float distanceDim(float dist, float strength)
{
	float brightness;
	brightness = 1/(dist*dist * strength + 1);
	return brightness;
}

subroutine vec3 applyLight();
subroutine uniform applyLight u_lProgram;

subroutine (applyLight)
vec3 p_withL()
{
	vec3 light = vec3(0,0,0);
	for(int i=0; i<u_lightCount; i++)
	{
		vec3 l = vec3(0,0,0);
		l += u_lightAmbient[i];
		l += u_lightDiffuse[i]  * u_kd;
		l *= distanceDim(distance(position, u_lightPosition[i]), u_lightStrength[i]);	
		light += l;
	}
	light.rgb = min(vec3(1,1,1).rgb, light.rgb);
	return light;
}


subroutine (applyLight)
vec3 p_outL()
{
	return vec3(1,1,1);
}

void main()
{

	float c = (float(gl_InstanceID) - firstPos) / float(count);
	 c += int(c < 0);
	 c = 1-c;

	 if(u_fadeWeight > 0)
	 {
		c*=u_fadeWeight;
		color.rgb = mix(inColor.rgb, u_fadeColor.rgb, c);	 
	 }else
	 {
		c*= -u_fadeWeight;
		color.rgb = mix(u_fadeColor.rgb, inColor.rgb, c);	 
	 }
	

	color.rgb *= u_lProgram();

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
	
	vec4 vert = vertex;	
	vert.rgb *= u_scale;

	gl_Position = projectionMatrix * modelView * vert;
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