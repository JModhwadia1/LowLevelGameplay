#pragma once

#include <SFML/Graphics.hpp>
class Animation
{
public:
	Animation() = default;
	Animation(int x, int y, int width, int height, std::string filePath)
	{
		//texture.loadFromFile("Textures/spritesheet.jpg");
		_texture.loadFromFile(filePath);
		//_texture = texture;
		for (int i = 0; i < numberOfFrames; i++)
		{
			//frames[i] = { x + i * width,y,x + (i + 1) * width, y + height };

			//frames[i] = { x,y + i * height,x + width, y + (i + 1) * height };
			frames[i] = { x, y + i * height, width, height };
			//frames[i] = { x + i * width, y, width, height };

		}

	}
	// Will set the actual texture to the spite required for the animation
	void ApplyToSprite(sf::Sprite& s) const
	{
		// Set the texture of the spriets
		s.setTexture(_texture);
		// Set the texture rect based on the index of the animation 
		s.setTextureRect(frames[indexFrame]);
	}
	void Update(float dt)
	{
		elapsedTime += dt;
		// Switch sprite
		while (elapsedTime >= holdTime)
		{
			elapsedTime -= holdTime;
			Advance();
		}
	}
private:
	void Advance()
	{
		// Check if the index is greater than the total amount of frames
		if (++indexFrame >= numberOfFrames)
		{
			indexFrame = 0;
		}

	}
private:
	static constexpr int numberOfFrames = 3;
	static constexpr float holdTime = 0.1f; // how long a frame will last till
	sf::Texture _texture;
	sf::IntRect frames[numberOfFrames]; // total amount of rects required for the animation
	int indexFrame = 0;		// index of the frame
	float elapsedTime = 0.0f; // time elapsed

};

