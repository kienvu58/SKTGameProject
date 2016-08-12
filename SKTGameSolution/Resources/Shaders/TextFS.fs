precision mediump float;
uniform vec4 u_color;
uniform sampler2D u_s_texture;
varying vec2 v_uv;
void main()
{
gl_FragColor = vec4(u_color.r, u_color.g, u_color.b, texture2D(u_s_texture, v_uv).a * u_color.a);
}
