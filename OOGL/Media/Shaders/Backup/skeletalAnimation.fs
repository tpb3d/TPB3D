// Skeletal Animation Fragment Shader

uniform sampler2D sampler0;

varying vec3 N, L;

void main(void)
{
	// lighting
	float intensity = max(0.0, dot(normalize(N), normalize(L)));
	intensity *= 0.40;

	vec4 texval0 = texture2D(sampler0, vec2(gl_TexCoord[0]));
 
	gl_FragColor = texval0;
	gl_FragColor.rgb += intensity;
}
