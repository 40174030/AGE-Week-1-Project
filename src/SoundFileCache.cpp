#include "stdafx.h"
#include "SoundFileCache.h"

SoundFileCache::SoundFileCache(void) {}

SoundFileCache::~SoundFileCache(void)
{
	std::for_each(sounds.begin(), sounds.end(), Deallocator<sf::SoundBuffer*>());
}

sf::Sound SoundFileCache::GetSound(std::string soundName) const
{
	std::map<std::string, sf::SoundBuffer *>::iterator itr = sounds.find(soundName);
	if (itr == sounds.end())
	{
		sf::SoundBuffer *soundBuffer = new sf::SoundBuffer();
		if (!soundBuffer->loadFromFile(soundName))
		{
			delete soundBuffer;
			throw SoundNotFoundExeception(
				soundName + " was not found in call to SoundFileCache::GetSound");
		}

		std::map<std::string, sf::SoundBuffer *>::iterator res =
			sounds.insert(std::pair<std::string, sf::SoundBuffer*>(soundName, soundBuffer)).first;

		sf::Sound sound;
		sound.setBuffer(*soundBuffer);
		sound.setVolume(25.0f);
		return sound;
	}
	else
	{
		sf::Sound sound;
		sound.setBuffer(*itr->second);
		return sound;
	}

	throw SoundNotFoundExeception(
		soundName + " was not found in call to SoundFileCache::GetSound");
}

std::map<std::string, sf::SoundBuffer*> SoundFileCache::sounds;
