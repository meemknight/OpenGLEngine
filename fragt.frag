#version 400
#define LIGHT_COUNT 32

/////////////////////////////////////////////
//fragt.frag
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////

uniform float u_time;
uniform vec3 u_eyePosition;
uniform sampler2D u_sampl;
uniform sampler2D u_samplN;

in vec2 v_texture;
in vec3 v_Normal;
in vec3 worldspace;

out vec4 outColor;

struct Material
{
float shiny;
vec3 ka;
vec3 kd;
vec3 ks;
};

struct Light {
	vec4 position;
  
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float strength;
};

uniform Material u_material;

uniform vec4 u_lightPosition[LIGHT_COUNT]; // last component determins if it is a directional light or not, 1 means positional // ???
uniform vec3 u_lightAmbient[LIGHT_COUNT];
uniform vec3 u_lightDiffuse[LIGHT_COUNT];
uniform vec3 u_lightSpecular[LIGHT_COUNT];
uniform float u_lightStrength[LIGHT_COUNT]; //used to determine the distance to shine,   0 means infinite distance
uniform int u_lightCount;



float distanceDim(float dist, float strength)
{
	float brightness;
	brightness = 1/(dist*dist * strength + 1);
	return brightness;
}

void unblend(inout vec3 a, float b)
{	
	a.rgb = (floor(a.rgb/b).rgb) * b;
}

vec3 phongModel(vec3 normal, const in Light light)
{
	float dist = abs(distance(worldspace, light.position.xyz));
	float distanceDimFactor = distanceDim(dist, light.strength);


	vec3 lightVectorWorld;
		if(light.position.a == 0.0)
		{
			lightVectorWorld = normalize(-light.position.xyz);
		}else
		{
			lightVectorWorld = normalize(light.position.xyz - worldspace); 
		}

	float diffusedBrightness = max(0, dot(lightVectorWorld, normal));
	

	float specularBrightness;
	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normal);
	vec3 eyeVector = normalize(u_eyePosition - worldspace);
	specularBrightness = dot(reflectedLightVectorWorld, eyeVector);
	specularBrightness = clamp(specularBrightness, 0, 1);
	//specularBrightness *= smoothstep(0, 0.1, diffusedBrightness); //ca sa scada lumina daca nu exista lumina diffused

	if(dot(eyeVector, lightVectorWorld) > -0.1)
	{
		//specularBrightness = 0;
	}
	
	specularBrightness = pow(specularBrightness, u_material.shiny);
	//


	vec3 ASD;

	 float edgeDetection = (dot(eyeVector, normal) > 0.3) ? 1 : 0;
	 edgeDetection = 1;
	 vec3 diff = diffusedBrightness * u_material.kd.rgb	* light.diffuse * edgeDetection * distanceDimFactor;
	 vec3 spec = specularBrightness * u_material.ks		* light.specular *			    distanceDimFactor;
	 vec3 ambb =		1			* u_material.ka.rgb	* light.ambient * edgeDetection * distanceDimFactor;

	 //unblend(diff, 7);
	 //unblend(spec, 7);

	ASD.rgb = vec3(diff) +
			  vec3(spec) + 
			  vec3(ambb);


	return vec3(ASD);
}

subroutine vec3 textreType(vec2 coordonates);
subroutine uniform textreType u_tProgram;

subroutine (textreType)
vec3 p_withT(vec2 coordonates)
{
	return texture2D(u_sampl, coordonates).rgb;
}

subroutine (textreType)
vec3 p_withoutT(vec2 coordonates)
{
	return vec3(1, 1, 1).rgb;
}

void main()
{
	vec3 inNormal = normalize(v_Normal);
	//inNormal =  inNormal.xyz + (texture2D(u_samplN, v_texture).xyz * 2 -1);

	//inNormal = normalize(inNormal);
	vec3 c = vec3(0, 0, 0);

	//if(!gl_FrontFacing){inNormal *=-1;}
	inNormal *= (1 - (int(!gl_FrontFacing)*2));

	Light l;

	for(int i=0; i<u_lightCount; i++)
	{
		l.position = u_lightPosition[i];
		l.ambient = u_lightAmbient[i];
		l.diffuse = u_lightDiffuse[i];
		l.specular = u_lightSpecular[i];
		l.strength = u_lightStrength[i];
		c.rgb += phongModel(inNormal, l).rgb;
	}

	c.r = min(1, c.r);
	c.g = min(1, c.g);
	c.b = min(1, c.b);

	//float gamma = 2.2;
	//c.rgb = pow(c.rgb, vec3(1.0/gamma));
	//unblend(c.rgb, 5);
	
	
	outColor = vec4(c.rgb * u_tProgram(v_texture), 0);	
	
		
}