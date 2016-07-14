attribute vec3 a_posL;
uniform mat4 u_mvp;
varying vec3 v_uvPos;

void main(void){
	gl_Position = u_mvp*vec4(a_posL,1);
	v_uvPos = a_posL;
}











