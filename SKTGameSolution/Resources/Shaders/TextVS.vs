attribute vec4 a_position; 
varying vec2 v_uv; 
void main() {
gl_Position = vec4(a_position.xy, 0, 1);
v_uv = a_position.zw;
}