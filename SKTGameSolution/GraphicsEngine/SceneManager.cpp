#include "SceneManager.h"
#include "ResourceManager.h"
#include "HelperFunctions.h"
#include "Camera.h"
#include <iostream>
#include "InputManager.h"
#include "Sprite.h"

#define MAX_CHAR_LENGTH 100

SceneManager* SceneManager::s_Instance = nullptr;


SceneManager::SceneManager(): m_iNumObjects(0)
{
};

SceneManager::~SceneManager()
{
	delete m_pCamera;
	Clear();
}

SceneManager* SceneManager::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new SceneManager();
	}
	return s_Instance;
}

void SceneManager::DestroyInstance()
{
	if (s_Instance)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
}

void SceneManager::Init(char* filePath)
{
//	FILE* pfile = fopen(filePath, "r");
//	if (!pfile)
//	{
//		std::cout << "Could not open file " << filePath << std::endl;
//		return;
//	}
//
//	m_mapObjects = new std::map<int, GraphicalObject*>();
//
//	fscanf(pfile, "#Objects: %d\n", &m_iNumObjects);
//
//	int i;
//	for (i = 0; i < m_iNumObjects; i++)
//	{
//		fscanf(pfile, "\n");
//
//		GraphicalObject* obj;
//
//		int id;
//		fscanf(pfile, "ID %d %*s\n", &id);
//
//		char typeObject[MAX_CHAR_LENGTH];
//		fscanf(pfile, "TYPE %s\n", typeObject);
//
//		if (strcmp(typeObject, "SPRITE") == 0)
//		{
//			obj = new Sprite();
//			float spriteX, spriteY, spriteW, spriteH, textureW, textureH;
//			fscanf(pfile, "COORD %f %f %f %f %f %f\n",
//			       &spriteX, &spriteY, &spriteW, &spriteH, &textureW, &textureH);
//			dynamic_cast<Sprite*>(obj)->InitSprite(spriteX, spriteY, spriteW, spriteH, textureW, textureH,
//			                                      Vector2(480/2, 854/2));
//		}
//		else
//		{
//			obj = new GraphicalObject();
//			int modelId;
//			fscanf(pfile, "MODEL %d\n", &modelId);
//			obj->SetModel(ResourceManager::GetInstance()->GetModelById(modelId));
//		}
//
//		int num2dTextures;
//		fscanf(pfile, "TEXTURES %d\n", &num2dTextures);
//		for (int j = 0; j < num2dTextures; j++)
//		{
//			int textureId;
//			fscanf(pfile, "TEXTURE %d\n", &textureId);
//			obj->Add2dTexture(ResourceManager::GetInstance()->GetTexturelById(textureId));
//		}
//
//		int numCubeTextures;
//		fscanf(pfile, "CUBETEXTURES %d\n", &numCubeTextures);
//		for (int j = 0; j < numCubeTextures; j++)
//		{
//			int cubeTextureId;
//			fscanf(pfile, "CUBETEXTURE %d\n", &cubeTextureId);
//			obj->AddCubeTexture(ResourceManager::GetInstance()->GetCubeTextureById(cubeTextureId));
//		}
//
//		int shaderId;
//		fscanf(pfile, "SHADER %d\n", &shaderId);
//		obj->SetShader(ResourceManager::GetInstance()->GetShadersById(shaderId));
//
//		if (strcmp(typeObject, "OBJECT") == 0)
//		{
//			obj->SetType(TypeObject::OBJECT);
//		}
//		else if (strcmp(typeObject, "SKYBOX") == 0)
//		{
//			obj->SetType(TypeObject::SKYBOX);
//		}
//		else
//		{
//			obj->SetType(TypeObject::SPRITE);
//		}
//
//		char tmp[MAX_CHAR_LENGTH];
//		Vector3 position;
//		fgets(tmp, sizeof(tmp), pfile);
//		sscanf(tmp, "POSITION %f %f %f\n", &position.x, &position.y, &position.z);
//
//		Vector3 rotation;
//		fgets(tmp, sizeof(tmp), pfile);
//		sscanf(tmp, "ROTATION %f %f %f\n", &rotation.x, &rotation.y, &rotation.z);
//
//		Vector3 scale;
//		fgets(tmp, sizeof(tmp), pfile);
//		sscanf(tmp, "SCALE %f %f %f\n", &scale.x, &scale.y, &scale.z);
//
//		obj->SetWorldMatrix(position, rotation, scale);
//
//		m_mapObjects->insert(std::pair<int, GraphicalObject*>(id, obj));
//	}
//	//read info for camera.
//	float n, f, fov, speed, sensitivity;
//	char cameraType[MAX_CHAR_LENGTH];
//	fscanf(pfile, "\n");
//	fscanf(pfile, "#CAMERA\n");
//	fscanf(pfile, "TYPE %s\n", &cameraType);
//	fscanf(pfile, "NEAR %f\n", &n);
//	fscanf(pfile, "FAR %f\n", &f);
//	fscanf(pfile, "FOV %f\n", &fov);
//	fscanf(pfile, "SPEED %f\n", &speed);
//	fscanf(pfile, "SENSITIVITY %f\n", &sensitivity);
//	fclose(pfile);
//	m_pCamera = new Camera();
//	if (strcmp(cameraType, "ORTHOGRAPHIC") == 0)
//	{
//		m_pCamera->SetCameraType(CameraType::ORTHOGRAPHIC);
//	}
//	else
//	{
//		m_pCamera->SetCameraType(CameraType::PERSPECTIVE);
//	}
//	m_pCamera->SetInfo(n, f, fov, speed, sensitivity);
//	m_pCamera->UpdateProjectionMatrix();
//	auto it = m_mapObjects->begin();
//	while (it != m_mapObjects->end())
//	{
//		it->second->SetProjectionMatrix(m_pCamera->GetProjectionMatrix());
//		++it;
//	}
}

void SceneManager::Draw()
{
//	auto it = m_mapObjects->begin();
//	while (it != m_mapObjects->end())
//	{
//		it->second->Render();
//		++it;
//	}
}

void SceneManager::Clear()
{
	ClearMap<GraphicalObject>(m_mapObjects);
}

void SceneManager::Update(float deltaTime)
{
//	// Move Camera
//	Vector3 direction(InputMgr->IsPressed(KEY_D) - InputMgr->IsPressed(KEY_A),
//	                          0,
//	                          InputMgr->IsPressed(KEY_S) - InputMgr->IsPressed(KEY_W)
//	);
//	m_pCamera->Move(direction, deltaTime);
//
//	// Rotate Camera
//	Vector2 lastMousePos = InputMgr->GetLastMousePosition();
//	Vector2 currentMousePos = InputMgr->GetCurrentMousePosition();
//	Vector2 offset = currentMousePos - lastMousePos;
//	InputMgr->SetLastMousePosition(currentMousePos.x, currentMousePos.y);
//	m_pCamera->Rotate(offset, deltaTime);
//
//	m_pCamera->UpdateViewMatrix();
//	auto it = m_mapObjects->begin();
//	while (it != m_mapObjects->end())
//	{
//		it->second->SetViewMatrix(m_pCamera->GetViewMatrix());
//		++it;
//	}
}

GraphicalObject* SceneManager::GetObjectById(int id)
{
	return GetResourceById<GraphicalObject>(id, m_mapObjects);
}
