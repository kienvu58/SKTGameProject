precision mediump float;
varying vec2 v_uv;

uniform sampler2D u_texture;
uniform vec2 u_delta;

void main()
{
	vec2 uv = v_uv + u_delta;
	gl_FragColor = texture2D(u_texture, uv);
}
