#pragma once
#include "stdafx.h"
#include "IAudioProvider.h"
#include "SoundFileCache.h"

class SFMLSoundProvider : public IAudioProvider
{
public:
	SFMLSoundProvider();

	void PlaySound(std::string filename);
	bool IsSoundPlaying();
	void StopSounds();

private:
	static const int sound_channels = 5;
	SoundFileCache soundFileCache;
	sf::Sound sounds[sound_channels];
};