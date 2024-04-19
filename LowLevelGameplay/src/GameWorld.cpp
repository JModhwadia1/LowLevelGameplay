#include "GameWorld.h"

GameWorld::GameWorld(sf::RenderWindow* window)
{
	mWindow = window;
	Init();
}

void GameWorld::Init()
{
	//mPlayerTex = new sf::Texture();
	//mEnemyTex = new sf::Texture();
	mResources.mPlayerTex = new sf::Texture();
	mResources.mBulletTex = new sf::Texture();
	mResources.mEnemyTex = new sf::Texture();
	if (!mResources.mPlayerTex->loadFromFile("Textures/player.png", sf::IntRect(0, 0, 5, 11)))
	{
		std::cout << "Player texture not loaded" << std::endl;
		return;
	}
	if (!mResources.mEnemyTex->loadFromFile("Textures/player.png", sf::IntRect(0, 0, 5, 11)))
	{
		std::cout << "Enemy texture not loaded" << std::endl;
		return;
	}

	if (!mResources.mBulletTex->loadFromFile("Textures/player.png", sf::IntRect(0, 0, 5, 11)))
	{
		std::cout << "Enemy texture not loaded" << std::endl;
		return;
	}

	mPlayer = new Player(this,mResources.mPlayerTex);
	mEnemy = new Enemy(this, mResources.mEnemyTex);



	mGameobjects.push_back(mPlayer);
	mGameobjects.push_back(mEnemy);
	
}

void GameWorld::Update(float DeltaTime)
{
	/*mPlayer->Update(DeltaTime);
	mEnemy->Update(DeltaTime);*/

	for (int i = 0; i < mGameobjects.size(); i++)
	{
		mGameobjects[i]->Update(DeltaTime);
	}


	UpdateCollisions();
}

void GameWorld::Render(sf::RenderWindow* window)
{
	/*mPlayer->Draw(window);
	mEnemy->Draw(window);*/


	for (int i = 0; i < mGameobjects.size(); i++)
	{
		mGameobjects[i]->Draw(window);
	}
}

void GameWorld::UpdateCollisions()
{
	CollisionManifold manifold;
	for (auto it = mGameobjects.begin(); it < mGameobjects.end(); ++it)
	{
		for (auto it2 = it + 1; it2 < mGameobjects.end(); ++it2)
		{
			GameObject* a = *it;
			GameObject* b = *it2;
			

			if (a != nullptr && b != nullptr)
			{
				if (a->IsCollideable() && b->IsCollideable() && a->GetCollider()->CollidesWith(*b->GetCollider(), manifold))
				{
					a->OnCollision(*b);
					b->OnCollision(*a);
				}
			}
		}
	}
}
