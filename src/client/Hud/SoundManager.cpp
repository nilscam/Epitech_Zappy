//
// EPITECH PROJECT, 2018
// zappy
// File description:
// SoundManager.cpp
//

#include "SoundManager.hpp"

SoundManager::SoundManager()
{
	_engine = irrklang::createIrrKlangDevice();

	sounds[SOUND_PLOC] = PATH_TO_SOUND "spyro1.mp3";
	sounds[SOUND_PLOC] = PATH_TO_SOUND "";
	musics[MUSIC_SPYRO_1] = PATH_TO_SOUND "spyro1.mp3";
	musics[MUSIC_SPYRO_2] = PATH_TO_SOUND "spyro2.mp3";
	musics[MUSIC_SPYRO_3] = PATH_TO_SOUND "spyro3.mp3";
	musics[MUSIC_SPYRO_4] = PATH_TO_SOUND "spyro4.mp3";
	musics[MUSIC_SPYRO_5] = PATH_TO_SOUND "spyro5.mp3";
	
	musicIDX = -1;
}

SoundManager::~SoundManager()
{	
}

void SoundManager::playNextMusic()
{
	if (musicIDX != -1)
		_engine->removeSoundSource(musics[musicIDX].c_str());
	musicIDX += 1;
	if (musicIDX >= (int)musics.size())
		musicIDX = 0;
	_engine->play3D(musics[musicIDX].c_str(),
			irrklang::vec3df(0, 0, 0), true,
			false, false);
}

void SoundManager::playSound(SoundManager::Sound sound, bool loop)
{
	_engine->play3D(sounds[sound].c_str(), irrklang::vec3df(0, 0, 0),
			loop, false, false);
}

void SoundManager::setVolume(float volume)
{
	volume = std::min(100.0, std::max(0.0, (double)volume));
	_engine->setSoundVolume(volume / 100.0);
}
