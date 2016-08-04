#pragma once
#include "../Utilities/utilities.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	sf::Music MainMenuMusic;
	sf::Music GamePlayMusic;
	sf::Music Skill;
	int InitMusic(char *type, char *fileName);
	int MusicPlay(char *type);
	int MusicPause(char *type);
	int MusicStop(char *type);
	int MusicLoop(char *type);
	int MusicVolume(char *type, int value);
};


