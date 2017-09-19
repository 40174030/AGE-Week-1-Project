#pragma once

class SoundFileCache
{
public:
	SoundFileCache(void);
	~SoundFileCache(void);

	sf::Sound GetSound(std::string) const;

private:
	static std::map<std::string, sf::SoundBuffer*> sounds;

	struct SoundFileDeallocator
	{
		void operator()(const std::pair<std::string, sf::SoundBuffer*> & p)
		{
			delete p.second;
		}
	};

	template <typename T>
	struct Deallocator {
		void operator()(const std::pair<std::string, T> &p)
		{
			delete p.second;
		}
	};
};


class SoundNotFoundExeception : public std::runtime_error
{
public:
	SoundNotFoundExeception(std::string const& msg) : std::runtime_error(msg) {}
};
