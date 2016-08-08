#pragma once
#include <vector>
#include "../Utilities/utilities.h"

enum class ShaderState {CULLING, DEPTH_TEST, ALPHA};

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLuint locationAttributePos;
	GLuint locationAttributeUV;
	GLuint locationUniformTex;
	GLuint locationUniformMVP;
	GLuint locationUniformTime;
	GLuint locationUniformDelta;
	GLuint locationUniformTexIndexAnimation;

	GLuint locationUniformTexture;
	GLuint locationAttributePosition;
	GLuint locationUniformColor;

	std::vector<ShaderState> states;
	
	int Init(const char * fileVertexShader, const char * fileFragmentShader);
	void EnableStates();
	void DisableStates();
	~Shaders();
};