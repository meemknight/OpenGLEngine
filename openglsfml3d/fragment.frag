#version 330 

in vec3 color;
uniform float u_time;
uniform vec3 u_ambience;
uniform float u_c;

struct material
{
float shinyness;
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

void ambience(inout vec4 color)
{
	color.rgb *= u_ambience.rgb;	
}

void unblend(inout vec4 color, int a)
{
	color.rgb *= a;
	color.r = floor(color.r);
	color.g = floor(color.g);
	color.b = floor(color.b);
	color.rgb /= a;
}

void outline(inout vec4 color, float margin)
{
	float difference = max(max(fwidth(color).x,fwidth(color).y),fwidth(color).z);

	//if(difference > 0.01){c = vec4(0,0,0,0);}

	int cc = int(!bool(step(margin, difference)));
	color.xyzw *= cc;
}


void main()
{
	vec4 c = vec4(color.xyz ,1);
	//timp(c);
	ambience(c);
	//unblend(c, 24);

	//outline(c, 0.0001);

	gl_FragColor = c;
		
}