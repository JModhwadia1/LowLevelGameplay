#include "GameWorld.h"
#include <chrono>




#define FIXEDFRAMERATE 0.016
class B
{
public:
	
	LLGP::Event<int> OnSomething;
	
	
	void BroadcastOnSomething(int arg1)
	{
		OnSomething(arg1);
	}
};
class A
{
private:
	B* other;
public:
	A();
	A(B* _other) : other(_other) { other->OnSomething += std::bind(&A::Handle_ThatSomething, this, std::placeholders::_1); }
	void Handle_ThatSomething(int in)
	{
		std::cout << in << std::endl;
		other->OnSomething -= std::bind(&A::Handle_ThatSomething, this, std::placeholders::_1);
	 }

};

void UsefulFunction(int a, int b)
{
	std::cout << a << b << std::endl;
}
int main()
{

	B uno;
	A dos(&uno);

	uno.OnSomething(50);
	uno.OnSomething(30);




	LLGP::Event<int, int>eventTest;

	eventTest += &UsefulFunction;
	eventTest(5, 6);

	

	

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	
	
	GameWorld* mWorld = new GameWorld(&window);

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

		mWorld->Update(deltaTime);
		
		/*mPlayer->Update(deltaTime);
		enemy->Update(deltaTime);
		
		

		CollisionManifold manifold;

		if (mPlayer->IsCollideable() && enemy->IsCollideable() && mPlayer->GetCollider()->CollidesWith(*enemy->GetCollider(), manifold))
		{
			std::cout << "COLLISION" << std::endl;
		}*/

		timeSincePhysicsStep += deltaTime;

		while (timeSincePhysicsStep > FIXEDFRAMERATE)
		{
			// Collect collision info
			// dispatch collisions

			mWorld->UpdateCollisions();

			timeSincePhysicsStep -= FIXEDFRAMERATE;
		}
		
		window.clear();
		/*mPlayer->Render(window);
		enemy->Draw(window);*/
		mWorld->Render(&window);
		window.display();
	}

	return 0;
}
