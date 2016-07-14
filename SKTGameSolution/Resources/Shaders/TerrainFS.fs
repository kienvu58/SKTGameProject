precision mediump float;
varying vec2 v_uv;

uniform sampler2D u_texture[4];

void main()
{
	vec4 blended = texture2D(u_texture[0], v_uv);
	vec4 dirt = texture2D(u_texture[1], v_uv);
	vec4 grass = texture2D(u_texture[2], v_uv);
	vec4 rock = texture2D(u_texture[3], v_uv);

	vec4 finalTexture = (blended.r*rock + blended.g*grass + blended.b*dirt)/(blended.r + blended.g + blended.b); 
	gl_FragColor = finalTexture;
}
