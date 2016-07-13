#include "SceneManager.h"
#include "ResourceManager.h"
#include "HelperFunctions.h"
#include "Camera.h"
#include <iostream>
#include "Globals.h"
#include "InputManager.h"

SceneManager* SceneManager::instance = 0;

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance() {
	if (instance == 0) {
		instance = new SceneManager();
	}
	return instance;
}

void SceneManager::Init(char *filePath) {
	FILE *pfile = fopen(filePath, "r");
	fscanf(pfile, "#Objects: %d\n", &m_iNumObjects);
	
	m_mapObjects = new std::map<int, Object*>();

	int i;
	for (i=0; i< m_iNumObjects; i++){
		fscanf(pfile, "\n");

		Object *obj = new Object();

		int id;
		fscanf(pfile, "ID %d\n", &id);
		
		char typeObject[200];
		fscanf(pfile, "TYPE %s\n", typeObject);
	
		int modelId;
		fscanf(pfile, "MODEL %d\n", &modelId);
		obj->SetModel(ResourceManager::GetInstance()->GetModelById(modelId));

		int num2dTextures;
		fscanf(pfile, "TEXTURES %d\n", &num2dTextures);
		for (int j=0; j<num2dTextures;j++){
			int textureId;
			fscanf(pfile, "TEXTURE %d\n", &textureId);
			obj->Add2dTexture(ResourceManager::GetInstance()->GetTexturelById(textureId));
		}

		int numCubeTextures;
		fscanf(pfile, "CUBETEXTURES %d\n", &numCubeTextures);
		for (int j=0; j<numCubeTextures; j++){
			int cubeTextureId;
			fscanf(pfile, "CUBETEXTURE %d\n", &cubeTextureId);
			obj->AddCubeTexture(ResourceManager::GetInstance()->GetCubeTextureById(cubeTextureId));
		}

		int shaderId;
		fscanf(pfile, "SHADER %d\n", &shaderId);
		obj->SetShader(ResourceManager::GetInstance()->GetShaderById(shaderId));

		if (strcmp(typeObject, "OBJECT") == 0) {
			obj->m_typType = TypeObject::OBJECT;
		}
		else if (strcmp(typeObject, "SKYBOX") == 0) {
			obj->m_typType = TypeObject::SKYBOX;
		}

		char tmp[200];
		Vector3 position;
		fgets(tmp, sizeof(tmp), pfile);
		sscanf(tmp, "POSITION %f, %f, %f\n", &position.x, &position.y, &position.z);
		obj->m_vec3Pos = position;

		Vector3 rotation;
		fgets(tmp, sizeof(tmp), pfile);
		sscanf(tmp, "ROTATION %f, %f, %f\n", &rotation.x, &rotation.y, &rotation.z);
		obj->m_vec3Rot = rotation;

		Vector3 scale;
		fgets(tmp, sizeof(tmp), pfile);
		sscanf(tmp, "SCALE %f, %f, %f\n", &scale.x, &scale.y, &scale.z);
		obj->m_vec3Scale = scale;

		m_mapObjects->insert(std::pair<int, Object*>(id, obj));
	}
	//read info for camera.
	fscanf(pfile, "\n");
	fscanf(pfile, "#CAMERA\n");
	fscanf(pfile, "NEAR %f\n", &(Camera::GetInstance()->m_fNear));
	fscanf(pfile, "FAR %f\n", &(Camera::GetInstance()->m_fFar));
	fscanf(pfile, "FOV %f\n", &(Camera::GetInstance()->m_fFov));
	fscanf(pfile, "SPEED %f\n", &(Camera::GetInstance()->m_fSpeed));
	fclose(pfile);
}

void SceneManager::Draw(){
	auto it = m_mapObjects->begin();
	while(it != m_mapObjects->end()){
		it->second->Draw();
		it++;
	}
}

void SceneManager::Clear(){
	ClearMap<Object>(m_mapObjects);
}

void SceneManager::Update(float deltaTime) {
	ProcessInput(deltaTime);
}
void SceneManager::ProcessInput(float deltaTime) {
	float speed = deltaTime*Camera::GetInstance()->m_fSpeed;
	if (InputManager::GetInstance()->m_iKeys & KEY_A) {
		Camera::GetInstance()->cameraPos -=
			(Camera::GetInstance()->cameraFront.Cross(Camera::GetInstance()->cameraUp)).Normalize()
			*speed;
	}
	if (InputManager::GetInstance()->m_iKeys & KEY_D) {
		Camera::GetInstance()->cameraPos +=
			(Camera::GetInstance()->cameraFront.Cross(Camera::GetInstance()->cameraUp)).Normalize()
			*speed;
	}
	if (InputManager::GetInstance()->m_iKeys & KEY_W) {
		Camera::GetInstance()->cameraPos +=
			Camera::GetInstance()->cameraFront*speed;
	}
	if (InputManager::GetInstance()->m_iKeys & KEY_S) {
		Camera::GetInstance()->cameraPos -=
			Camera::GetInstance()->cameraFront*speed;
	}
}

Object* SceneManager::GetObjectById(int id) {
	return GetResourceById<Object>(id, m_mapObjects);
}


