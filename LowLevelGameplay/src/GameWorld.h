#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Event.h"
#include <iostream>




class GameWorld
{
public:
	GameWorld(sf::RenderWindow* window);
	void Init();
	void Update(float DeltaTime);
	void Render(sf::RenderWindow* window);
	Player* GetPlayer() const { return mPlayer; }
	
	template <typename T>
	T* SpawnGameobject();

	void UpdateCollisions();

private:
	
	Player* mPlayer = nullptr;
	Enemy* mEnemy = nullptr;

	sf::Texture* mPlayerTex;
	sf::Texture* mEnemyTex;

	std::vector<GameObject*> mGameobjects;

};

template<typename T>
T* GameWorld::SpawnGameobject() 
{
	if (T* newGameobject = new T(*this)) 
	{
		mGameobjects.push_back(newGameobject);

		return mGameobjects;
	}
	return nullptr;
}

