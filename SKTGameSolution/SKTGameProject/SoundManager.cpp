#include "SoundManager.h"
#include "../include/SFML/Audio.hpp"


SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

int SoundManager::InitMusic(char *type, char * fileName)
{
	if (type == "MainMenu")
	{
		if (!MainMenuMusic.openFromFile(fileName))
			return 0;
	}
	else if (type == "GamePlay")
	{
		if (!GamePlayMusic.openFromFile(fileName))
			return 0;
	}
	else if (type == "Skill")
	{
		if (!Skill.openFromFile(fileName))
			return 0;
	}

}

int SoundManager::MusicPlay(char *type)
{
	if (type == "MainMenu")
		MainMenuMusic.play();
	else if (type == "GamePlay")
		GamePlayMusic.play();
	else if (type == "Skill")
		Skill.play();
	return 0;
}

int SoundManager::MusicPause(char *type)
{
	if (type == "GamePlay")
		GamePlayMusic.pause();
	return 0;
}

int SoundManager::MusicStop(char *type)
{

	if (type == "MainMenu")
		MainMenuMusic.stop();
	else if (type == "GamePlay")
		GamePlayMusic.stop();
	else if (type == "Skill")
		Skill.stop();
	return 0;
}

int SoundManager::MusicLoop(char *type)
{
	if (type == "MainMenu")
		MainMenuMusic.setLoop(1);
	else if (type == "GamePlay")
		GamePlayMusic.setLoop(1);
	return 0;
}

int SoundManager::MusicVolume(char *type, int value)
{
	if (type == "MainMenu")
		MainMenuMusic.setVolume(value);
	else if (type == "GamePlay")
		GamePlayMusic.setVolume(value);
	else if (type == "Skill")
		Skill.setVolume(value);
	return 0;
}
