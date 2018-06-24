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
	sounds[MENU_OK] = std::string(PATH_TO_SOUNDS) + "menu-ok.mp3";
	sounds[SOUND_POP] = std::string(PATH_TO_SOUNDS) + "bubble_pop.mp3";
	sounds[SOUND_INVOCATION] = std::string(PATH_TO_SOUNDS) + "yoshi_invocation.mp3";
	sounds[SOUND_YOSHI_KICK] = std::string(PATH_TO_SOUNDS) + "yoshi_kick.mp3";
	sounds[SOUND_YOSHI_POP] = std::string(PATH_TO_SOUNDS) + "yoshi_pop.mp3";
	sounds[SOUND_YOSHI_WAAH] = std::string(PATH_TO_SOUNDS) + "yoshi_waah.mp3";
	sounds[SOUND_YOSHI_YOSH] = std::string(PATH_TO_SOUNDS) + "yoshi_yosh.mp3";
	musics[MUSIC_SPYRO_1] = std::string(PATH_TO_MUSICS) + "spyro1.mp3";
	musics[MUSIC_SPYRO_2] = std::string(PATH_TO_MUSICS) + "spyro2.mp3";
	musics[MUSIC_SPYRO_3] = std::string(PATH_TO_MUSICS) + "spyro3.mp3";
	musics[MUSIC_SPYRO_4] = std::string(PATH_TO_MUSICS) + "spyro4.mp3";
	musics[MUSIC_SPYRO_5] = std::string(PATH_TO_MUSICS) + "spyro5.mp3";
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
