precision mediump float;
varying vec2 v_uv;

uniform sampler2D u_texture[3];
uniform float u_time;

void main()
{
	vec2 disp = texture2D(u_texture[1], vec2(v_uv.x, v_uv.y + u_time)).rg;
	vec2 offset = (2.0 * disp - 1.0) * 1.5;
	vec2 Tex_coords_displaced = v_uv + offset;
	vec4 fire_color = texture2D(u_texture[0], Tex_coords_displaced);
	vec4 AlphaValue = texture2D(u_texture[2], v_uv);
	//gl_FragColor = texture2D(u_texture[2], v_uv);
	gl_FragColor = fire_color * (1.0, 1.0, 1.0, AlphaValue.r);
}
