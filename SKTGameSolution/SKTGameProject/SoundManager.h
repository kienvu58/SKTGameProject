#pragma once
#include "../Utilities/utilities.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <map>
using namespace std;
class SoundManager
{
public:
	SoundManager();
	~SoundManager();
//	sf::Music MainMenuMusic;
//	sf::Music GamePlayMusic;
//	sf::Music Skill;
	map<char*, sf::Music*> music;
	sf::Music* m_MainMenuMusic = new sf::Music();
	sf::Music* m_GamePlayMusic = new sf::Music();
	sf::Music* m_SkillMusic = new sf::Music();
	int InitMusic(char *type, char *fileName);
	int MusicPlay(char *type);
	int MusicPause(char *type);
	int MusicStop(char *type);
	int MusicLoop(char *type);
	int MusicVolume(char *type, int value);
};


