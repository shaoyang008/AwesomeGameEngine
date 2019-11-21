#version 330

const float pi = 3.14159f;

in vec3 position;
in vec3 normalVec, lightVec, eyeVec;

uniform vec3 diffuse, specular;
uniform float shininess;

uniform vec3 Ambient;
uniform vec3 Light;

void main()
{
   	vec3 Kd = diffuse;
	vec3 Ks = specular;
	float alpha = shininess;

	vec3 N = normalize(normalVec);
	vec3 L = normalize(lightVec);
	vec3 V = normalize(eyeVec);
	vec3 H = normalize(L+V);

	float LN = max(dot(L,N),0.0);
	float HN = max(dot(H,N),0.0);
	float LH = max(dot(L,H),0.0);
	
	vec3  F = Ks + (vec3(1, 1, 1) - Ks) * pow((1 - LH), 5);
	float G = 1 / (dot(L,H) * dot(L,H));
	float D = (alpha + 2) / (2 * pi) * pow(HN, alpha);
	if(HN == 0 && alpha == 0) discard;
	
	gl_FragColor.xyz = Ambient * Kd + Light * LN * (Kd / pi + F * G * D / 4);
}