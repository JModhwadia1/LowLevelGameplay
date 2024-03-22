#include <SFML/Graphics.hpp>
#include <chrono>
#include "Player.h"
#include <iostream>
#include "Event.h"


#define FIXEDFRAMERATE 0.016

//class B
//{
//public:
//	LLGP::Event<int> OnSomething;
//	
//	void BroadcastOnSomething(int arg1)
//	{
//		OnSomething(arg1);
//	}
//private:
//
//};
//
//class A
//{
//public:
//	A(B*other)
//
//private:
//	B* other;
//};









int main()
{
	Player* mPlayer = nullptr;

	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	sf::Texture texture;
	if (!texture.loadFromFile("Textures/player.png", sf::IntRect(0,0,5,11)))
	{
		return EXIT_FAILURE;
	}
	/*std::shared_ptr<sf::Texture> sharedtexture = std::make_shared<sf::Texture>();
	sharedtexture->loadFromFile("Textures/player.png", sf::IntRect(0, 0, 5, 11));*/
	mPlayer = new Player(&texture);

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


		mPlayer->Update(deltaTime);
		
		timeSincePhysicsStep += deltaTime;

		while (timeSincePhysicsStep > FIXEDFRAMERATE)
		{
			// Collect collision info
			// dispatch collisions

			std::cout << "Hello WOrld" << std::endl;

			timeSincePhysicsStep -= FIXEDFRAMERATE;
		}
		
		window.clear();
		mPlayer->Render(window);
		window.display();
	}

	return 0;
}
