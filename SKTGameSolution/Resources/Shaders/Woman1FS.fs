precision mediump float;
varying vec2 v_uv;

uniform sampler2D u_texture[1];

void main()
{
	gl_FragColor = texture2D(u_texture[0], v_uv);
}
