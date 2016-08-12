precision mediump float;
varying vec2 v_uv;

uniform sampler2D u_texture;
uniform vec2 u_delta;
uniform float u_alpha;

void main()
{
	vec2 uv = v_uv + u_delta;
	vec4 texture = texture2D(u_texture, uv);
	gl_FragColor = vec4(texture.rgb, texture.a * u_alpha);
}
