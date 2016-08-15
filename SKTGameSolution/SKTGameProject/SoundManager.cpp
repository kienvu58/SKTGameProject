#include "SoundManager.h"
#include "../include/SFML/Audio.hpp"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
//	delete m_MainMenuMusic;
//	delete m_GamePlayMusic;
//	delete m_SkillShot;
//	delete m_SkillUlti_1;
//	delete m_SkillUlti_2;
//	delete m_GokuDead;
}

int SoundManager::InitMusic(char *type, char *fileName)
{

//	music.insert(std::pair<char*, sf::Music*>("MainMenu", m_MainMenuMusic));
//	music.insert(std::pair<char*, sf::Music*>("GamePlay", m_GamePlayMusic));
//	music.insert(std::pair<char*, sf::Music*>("SkillUlti_1", m_SkillUlti_1));
//	music.insert(std::pair<char*, sf::Music*>("SkillUlti_2", m_SkillUlti_2));
//	music.insert(std::pair<char*, sf::Music*>("SkillShot", m_SkillShot));
//	music.insert(std::pair<char*, sf::Music*>("GokuDead", m_GokuDead));
//	if (!music[type]->openFromFile(fileName))
		return 0;
//	return 1;
}

int SoundManager::MusicPlay(char *type)
{
//	music[type]->play();
	return 0;
}

int SoundManager::MusicPause(char *type)
{
//	music[type]->pause();
	return 0;
}

int SoundManager::MusicStop(char *type)
{

//	music[type]->stop();
	return 0;
}

int SoundManager::MusicLoop(char *type)
{
//	music[type]->setLoop(1);
	return 0;
}

int SoundManager::MusicVolume(char *type, float value)
{
//	music[type]->setVolume(value);
	return 0;
}
