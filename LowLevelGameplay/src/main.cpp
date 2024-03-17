#include <SFML/Graphics.hpp>
#include <chrono>
#include "Player.h"




int main()
{
	Player* mPlayer = nullptr;

	sf::RenderWindow window(sf::VideoMode(1200, 1200), "SFML works!");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	sf::Texture texture;
	if (!texture.loadFromFile("Textures/player.png", sf::IntRect(0,0,5,11)))
	{
		return EXIT_FAILURE;
	}

	mPlayer = new Player(texture);

	auto timePoint = std::chrono::steady_clock::now();

	/*sf::Sprite sprite(texture);*/

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Get Deltatime
		float dt;
		{
			const auto newTimePoint = std::chrono::steady_clock::now();
			dt = std::chrono::duration<float>(newTimePoint - timePoint).count();
			timePoint = newTimePoint;
		}

		mPlayer->Update(dt);
		
		window.clear();
		mPlayer->Render(window);
		window.display();
	}

	return 0;
}
