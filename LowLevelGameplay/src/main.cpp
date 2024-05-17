#include "GameWorld.h"
#include <chrono>
#include "Constants.h"




int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	

	/*GameWorld* mWorld = new GameWorld(&window);*/
	GameWorld::Init(&window);

	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();

	float deltaTime = 0.0f;

	/*sf::Sprite sprite(texture);*/
	float timeSincePhysicsStep = 0.0f; 

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime).count() / 1000000.f;
		lastTime = now;
		
	
		GameWorld::Update(deltaTime);
		timeSincePhysicsStep += deltaTime;
		
		while (timeSincePhysicsStep > FIXEDFRAMERATE)
		{
			// Collect collision info
			// dispatch collisions

			GameWorld::FixedUpdate(FIXEDFRAMERATE);
			GameWorld::UpdateCollisions();

			timeSincePhysicsStep -= FIXEDFRAMERATE;
		}
		
		window.clear();
		GameWorld::Render(&window);
		window.display();
	}

	return 0;
}
