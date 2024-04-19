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
	void Init();
	void Update(float DeltaTime);
	void Render(sf::RenderWindow* window);
	Player* GetPlayer() const { return mPlayer; }
	const Resources& GetResources() { return mResources; }
	void AddToGameobjects(GameObject* gameobject) { mGameobjects.push_back(gameobject); }

	template <typename T>
	T* SpawnGameobject(sf::Texture* tex);

	void UpdateCollisions();
	sf::RenderWindow* mWindow;

private:
	Player* mPlayer = nullptr;
	Enemy* mEnemy = nullptr;
	Resources mResources;
	std::vector<GameObject*> mGameobjects;
};

template<typename T>
T* GameWorld::SpawnGameobject(sf::Texture* tex) 
{
	if (T* newGameobject = new T(this, tex)) 
	{
		mGameobjects.push_back(newGameobject);
		return newGameobject;
	}
	return nullptr;
}

