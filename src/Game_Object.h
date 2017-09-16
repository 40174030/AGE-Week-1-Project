#pragma once


class Game_Object
{
public:
	Game_Object();
	virtual ~Game_Object();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow& window);
	virtual void Update(float elapsedTime);
	virtual void Reset();

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
	virtual bool IsLoaded() const;
	virtual bool HasVanished() const;

	virtual std::string GetFilename() const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;

protected:
	sf::Sprite& GetSprite();
	void Vanish();

private:
	sf::Sprite sprite;
	sf::Texture image;
	std::string filename;
	bool isLoaded;
	bool vanished;
};