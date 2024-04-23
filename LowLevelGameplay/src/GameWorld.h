#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Event.h"
#include <iostream>





class GameWorld
{
public:

	struct Resources {
		sf::Texture* mPlayerTex;
		sf::Texture* mEnemyTex;
		sf::Texture* mBulletTex;
	};


public:
	 GameWorld(sf::RenderWindow* window);
	const float arenaSize = 900;
	void Init();
	void Update(float DeltaTime);
	void Render(sf::RenderWindow* window);
	Player* GetPlayer() const { return mPlayer; }
	const Resources& GetResources() { return mResources; }
	void AddToGameobjects(GameObject* gameobject) { mGameobjects.push_back(gameobject); }

	void RenderArenaBounds();
	bool IsGameobjectOutOfBounds(GameObject* gameobject);
	template <typename T>
	T* SpawnGameobject(sf::Texture* texture);
	void UpdateCollisions();
	sf::RenderWindow* mWindow;

	void UpdateArenaBounds(float dt);

private:
	Player* mPlayer = nullptr;
	Enemy* mEnemy = nullptr;
	Resources mResources;
	std::vector<GameObject*> mGameobjects;
};

template<typename T>
T* GameWorld::SpawnGameobject(sf::Texture* texture) 
{
	if (T* newGameobject = new T(this, texture)) 
	{
		mGameobjects.push_back(newGameobject);
		return newGameobject;
	}
	return nullptr;
}

