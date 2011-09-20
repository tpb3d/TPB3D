// Skeletal Animation Vertex Shader

const int maxBones = 40;

attribute float boneAttribute;

uniform vec3 lightPos0;
uniform mat4 vertexTransformations[maxBones];

varying vec3 normal, light, halfVector;

void main(void)
{
	// Animation
	int bone = int(boneAttribute);
	mat4 vertexAnimation = (bone >= 0 && bone < maxBones) ? vertexTransformations[bone] : mat4(1.0);

	// GLSL 1.10 compatible version of mat3 normalAnimation = mat3(vertexAnimation);
	mat3 normalAnimation = mat3(vec3(vertexAnimation[0]), vec3(vertexAnimation[1]), vec3(vertexAnimation[2]));

	// lighting
	vec4 viewVertex = gl_ModelViewMatrix * vertexAnimation * gl_Vertex;
	
	light = normalize(gl_LightSource[0].position.xyz - viewVertex.xyz);
	normal = normalize(gl_NormalMatrix * normalAnimation * gl_Normal);
	halfVector = normalize(gl_LightSource[0].halfVector.xyz);

	// position
	gl_Position = gl_ModelViewProjectionMatrix * vertexAnimation * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;	
}
