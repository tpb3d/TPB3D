// Skeletal Animation Fragment Shader

uniform sampler2D sampler0;

varying vec3 normal, light, halfVector;

void main(void)
{
	vec4 texval0 = texture2D(sampler0, vec2(gl_TexCoord[0]));
	
	vec3 interpolatedNormal = normalize(normal);	

	vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * max(dot(interpolatedNormal, light), 0.0);

	vec4 ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;

	vec4 specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(max(dot(interpolatedNormal, halfVector), 0.0), gl_FrontMaterial.shininess);

	gl_FragColor = ambient + (diffuse * texval0) + specular;
}
