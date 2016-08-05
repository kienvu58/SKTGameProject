#include "SoundManager.h"
#include "../include/SFML/Audio.hpp"
#include <SFML/Audio/Music.hpp>
#include <map>

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	delete m_MainMenuMusic;
	delete m_GamePlayMusic;
	delete m_SkillMusic;
}

int SoundManager::InitMusic(char *type, char *fileName)
{

	music.insert(std::pair<char*, sf::Music*>("MainMenu", m_MainMenuMusic));
	music.insert(std::pair<char*, sf::Music*>("GamePlay", m_GamePlayMusic));
	music.insert(std::pair<char*, sf::Music*>("Skill", m_SkillMusic));
	
	if (!music[type]->openFromFile(fileName))
		return 0;
}

int SoundManager::MusicPlay(char *type)
{
	music[type]->play();	
	return 0;
}

int SoundManager::MusicPause(char *type)
{
	music[type]->pause();
	return 0;
}

int SoundManager::MusicStop(char *type)
{

	music[type]->stop();
	return 0;
}

int SoundManager::MusicLoop(char *type)
{
	music[type]->setLoop(1);
	return 0;
}

int SoundManager::MusicVolume(char *type, int value)
{
	music[type]->setVolume(value);
	return 0;
}
