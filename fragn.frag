#version 330

/////////////////////////////////////////////
//fragn.frag
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////

uniform float u_time;
uniform vec4 u_lightPosition;
uniform vec3 u_eyePosition;

in vec3 color;
in vec3 outNormal;
in vec3 worldspace;   // to rename   ,worldspace

struct material
{
float shiny;
vec3 ka;
vec3 kd;
vec3 ks;
};


uniform material u_material;


void timp(inout vec4 color)
{
	
	float time = u_time / 400;
	float val =	cos(time)+sin(time)*cos(time);

	color = mix(color, vec4(0.0, 0.0, 0.0, 1.0), val);
}


void unblend(inout vec4 color, int a)
{
	color.rgb *= a;
	color.rgb = floor(color.rgb);
	color.rgb /= a;
}


void removeByDistance(inout float brightness, float dist)
{
	brightness *= 1/( 0.9 + dist*0.1 + dist * dist * 0.001);
	brightness += 0.2;
	brightness = min(1, brightness);
	brightness = smoothstep(0.21, 1, brightness);  //ca sa dispara lumina
}


vec4 phongModel(vec3 normal, vec3 color)
{
	vec3 lightVectorWorld;
		if(u_lightPosition.a == 1)
		{
			 lightVectorWorld = normalize(u_lightPosition.xyz - worldspace);
		}else
		{
			 lightVectorWorld = normalize(-u_lightPosition.xyz);
		}

	float diffusedBrightness = max(0, dot(lightVectorWorld, normal));
	float dist = abs(distance(worldspace, u_lightPosition.xyz));

	removeByDistance(diffusedBrightness, dist);

	float specularBrightness;
	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normal);
	vec3 eyeVector = normalize(u_eyePosition - worldspace);
	specularBrightness = dot(reflectedLightVectorWorld, eyeVector);
	
	
	specularBrightness = clamp(specularBrightness, 0, 1);
	//specularBrightness *= smoothstep(0, 0.1, diffusedBrightness); //ca sa scada lumina daca nu exista lumina diffused
	//specularBrightness *= diffusedBrightness;
	specularBrightness = pow(specularBrightness, u_material.shiny);
	//specularBrightness *= 1.4;
	removeByDistance(specularBrightness, dist);

	vec3 ASD;
	//ASD.r = diffusedBrightness + specularBrightness + u_ambience.r;
	//ASD.g = diffusedBrightness + specularBrightness + u_ambience.g;
	//ASD.b = diffusedBrightness + specularBrightness + u_ambience.b;
	ASD.rgb = vec3(diffusedBrightness * u_material.kd.rgb) + (specularBrightness * u_material.ks.rgb) + (u_material.ka.rgb);

	ASD*=color;

	return vec4(ASD ,0);
}



void main()
{
	vec3 inNormal = normalize(outNormal);
	vec4 c;

	//if(!gl_FrontFacing){inNormal *=-1;}
	inNormal *= (1 - (int(!gl_FrontFacing)*2));

	c = phongModel(inNormal, color);
	
	//unblend(c, 24);
	
	gl_FragColor = c ;
		
}