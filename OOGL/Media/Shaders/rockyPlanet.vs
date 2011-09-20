// Diffuse Light Shader

uniform vec3 lightPos0;

varying vec3 normal, light; //, halfVector;

void main(void)
{
	vec4 viewVertex = gl_ModelViewMatrix * gl_Vertex;
	
	light = normalize(gl_LightSource[0].position.xyz - viewVertex.xyz);
	normal = normalize(gl_NormalMatrix * gl_Normal);
//	halfVector = normalize(gl_LightSource[0].halfVector.xyz);

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_MultiTexCoord1;
}
