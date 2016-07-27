#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	locationAttributePos = glGetAttribLocation(program, "a_posL");
	locationAttributeUV = glGetAttribLocation(program, "a_uv");
	locationUniformMVP = glGetUniformLocation(program, "u_mvp");
	locationUniformTex = glGetUniformLocation(program, "u_texture");
	locationUniformTime = glGetUniformLocation(program, "u_time");
	locationUniformDelta = glGetUniformLocation(program, "u_delta");
	locationUniformTexIndexAnimation = glGetUniformLocation(program, "u_texIndex");
	
	locationUniformTexture = glGetUniformLocation(program, "u_s_texture");
	locationAttributePosition = glGetAttribLocation(program, "a_position");
	locationUniformColor = glGetUniformLocation(program, "u_color");
	return 0;
}

void Shaders::EnableStates() {
	for (int i = 0; i < states.size(); i++) {
		switch (states[i]) {
		case ShaderState::CULLING:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			break;
		case ShaderState::DEPTH_TEST:
			glEnable(GL_DEPTH_TEST);
			break;
		case ShaderState::ALPHA:
			break;
		default:
			break;
		}
	}
}

void Shaders::DisableStates() {
	for (int i = 0; i < states.size(); i++) {
		switch (states[i]) {
		case ShaderState::CULLING:
			glDisable(GL_CULL_FACE);
			break;
		case ShaderState::DEPTH_TEST:
			glDisable(GL_DEPTH_TEST);
			break;
		case ShaderState::ALPHA:
			break;
		default:
			break;
		}
	}
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}