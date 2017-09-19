#include "stdafx.h"
#include "SFMLSoundProvider.h"

SFMLSoundProvider::SFMLSoundProvider() {}

void SFMLSoundProvider::PlaySound(std::string filename)
{
	int availableChannel = -1;
	for (int i = 0; i < sound_channels; i++)
	{
		if (sounds[i].getStatus() != sf::Sound::Playing)
		{
			availableChannel = i;
			break;
		}
	}
	
	// If all sound channels are in use, do nothing for now
	if (availableChannel != -1)
	{
		try
		{
			sounds[availableChannel] = soundFileCache.GetSound(filename);
			sounds[availableChannel].play();
		}
		catch (SoundNotFoundExeception& snfe)
		{
			// ERROR, file wasnt found, should handle error here
			// Currently, this will simply mean nothing happens if an error occurs
		}
	}
}

bool SFMLSoundProvider::IsSoundPlaying()
{
	for (int i = 0; i < sound_channels; i++)
	{
		if (sounds[i].getStatus() == sf::Sound::Playing)
			return true;
	}
	return false;
}

void SFMLSoundProvider::StopSounds()
{
	for (int i = 0; i < sound_channels; i++)
	{
		sounds[i].stop();
	}
}