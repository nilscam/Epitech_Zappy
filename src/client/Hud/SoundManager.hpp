//
// EPITECH PROJECT, 2018
// SoundManager.hpp
// File description:
// SoundManager.hpp
//

#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#define PATH_TO_MUSICS "./Ress/musics/"
#define PATH_TO_SOUNDS "./Ress/sounds/"

#include "include.hpp"
#include <iostream>
#include <cstddef>
#include <vector>
#include <string>
#include <map>

class SoundManager
{
public:
	enum Sound {
		MUSIC_SPYRO_1,
		MUSIC_SPYRO_2,
		MUSIC_SPYRO_3,
		MUSIC_SPYRO_4,
		MUSIC_SPYRO_5,
		SOUND_POP,
		SOUND_INVOCATION,
		SOUND_YOSHI_KICK,
		SOUND_YOSHI_POP,
		SOUND_YOSHI_YOSH,
		SOUND_YOSHI_WAAH
	};
	
	SoundManager();
	~SoundManager();
	void playNextMusic();
	void playSound(SoundManager::Sound sound, bool loop = false);
	void setVolume(float volume);
	int musicIDX;
	irrklang::ISoundEngine *_engine;
	
private:
	std::map<int, std::string> sounds;
	std::map<int, std::string> musics;
};

#endif
