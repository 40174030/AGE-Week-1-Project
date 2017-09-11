#pragma once
class Game_Object
{
public:
	Game_Object();
	virtual ~Game_Object();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow& window);
	virtual void Update(float elapsedTime);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
	virtual bool IsLoaded() const;

	virtual float GetWidth() const;
	virtual float GetHeight() const;

	virtual sf::FloatRect GetBoundingRect() const;

	virtual void Reset();


protected:
	sf::Sprite& GetSprite();

private:
	sf::Sprite sprite;
	sf::Texture image;
	std::string filename;
	bool isLoaded;
};