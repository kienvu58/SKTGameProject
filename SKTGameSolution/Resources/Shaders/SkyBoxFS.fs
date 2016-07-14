precision mediump float;
uniform samplerCube u_texture[1];
varying vec3 v_uvPos;

void main(void){
	gl_FragColor = textureCube(u_texture[0], v_uvPos);
}




