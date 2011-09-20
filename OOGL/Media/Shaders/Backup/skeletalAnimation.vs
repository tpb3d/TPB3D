// Skeletal Animation Vertex Shader

const int maxBones = 40;

attribute float boneAttribute;

uniform vec3 lightPos0;
uniform mat4 vertexTransformations[maxBones];

varying vec3 normal, light, halfVector;

void main(void)
{
	// Animation
	int bone = (int) boneAttribute;	
	mat4 vertexAnimation = (bone >= 0 && bone < maxBones) ? vertexTransformations[bone] : mat4(1.0);
	mat3 normalAnimation = mat3(vertexAnimation);

	// lighting
//	gl_FrontColor = gl_Color;
	vec4 worldVertex = gl_ModelViewMatrix * vertexAnimation * gl_Vertex;
	light = lightPos0 - worldVertex.xyz;
	N = gl_NormalMatrix * normalAnimation * gl_Normal;

	// position	
	gl_Position = gl_ModelViewProjectionMatrix * vertexAnimation * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;	
}
