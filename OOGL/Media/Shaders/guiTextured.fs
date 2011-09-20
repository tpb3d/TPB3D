// Diffuse Light Shader

uniform sampler2D sampler0;

void main(void)
{
   vec4 texval0 = texture2D(sampler0, vec2(gl_TexCoord[0]));
   
   gl_FragColor = texval0;
}
