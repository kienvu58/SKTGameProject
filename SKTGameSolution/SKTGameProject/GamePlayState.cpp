#include "GamePlayState.h"
#include "../GraphicsEngine/Vertex.h"


GamePlayState::GamePlayState()
{
}

void GamePlayState::Enter(Game* game)
{
	Vertex verticesData[4];
	int spriteW, spriteH, spriteX, spriteY, textureW, textureH;
	spriteX = 0;
	spriteY = 0;
	spriteW = 128;
	spriteH = 128;
	textureW = 1024;
	textureH = 1024;
	verticesData[0].pos = Vector3(-(float)spriteW / 2, -(float)spriteH / 2, 0.0f);
	verticesData[1].pos = Vector3((float)spriteW / 2, -(float)spriteH / 2, 0.0f);
	verticesData[2].pos = Vector3(-(float)spriteW / 2, (float)spriteH / 2, 0.0f);
	verticesData[3].pos = Vector3((float)spriteW / 2, (float)spriteH / 2, 0.0f);

	verticesData[0].uv = Vector2((float)spriteX / textureW, (float)(textureH - spriteY - spriteH) / textureH);
	verticesData[1].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)(textureH - spriteY - spriteH) / textureH);
	verticesData[2].uv = Vector2((float)spriteX / textureW, (float)(textureH - spriteY) / textureH);
	verticesData[3].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)(textureH - spriteY) / textureH);
	static Model modelGoku;
	modelGoku.LoadModel(verticesData, 4);
	static Texture spriteSheet;
	spriteSheet.LoadTGAFile("../Resources/Textures/SpriteSheetSSGoku.tga");
	static Shaders shaders;
	shaders.Init("../Resources/Shaders/SpriteVS.vs", "../Resources/Shaders/SpriteFS.fs");
	static Sprite spriteGoku;
	spriteGoku.SetModel(&modelGoku);
	spriteGoku.SetTexture(&spriteSheet);
	spriteGoku.SetShaders(&shaders);
	
	m_Goku.m_pSprite = &spriteGoku;

}

void GamePlayState::Execute(Game* game)
{
	m_Goku.Update();
}

void GamePlayState::Exit(Game* game)
{
}

void GamePlayState::Render(Game* game)
{
	if (m_Goku.m_pSprite)
		m_Goku.m_pSprite->Render();
}

GamePlayState* GamePlayState::GetInstance()
{
	static GamePlayState instance;
	return &instance;
}

GamePlayState::~GamePlayState()
{
}
