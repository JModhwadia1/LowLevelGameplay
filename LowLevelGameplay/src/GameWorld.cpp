#include "GameWorld.h"
#include "Vector2.h"
#include "Bullet.h"






GameWorld::GameWorld(sf::RenderWindow* window)
{
	mWindow = window;
	Init();
}

GameWorld::~GameWorld()
{
	mPlayer->OnPlayerDied -= std::bind(&GameWorld::HandlePlayerDied, this, std::placeholders::_1);
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
	mPlayer->OnPlayerDied += std::bind(&GameWorld::HandlePlayerDied, this, std::placeholders::_1);
	mEnemy = new Enemy(this, mResources.mEnemyTex);
	mPlayer->GetTransform()->SetPosition(LLGP::Vector2f(960.0f, 540.0f));



	mGameobjects.push_back(mPlayer);
	mGameobjects.push_back(mEnemy);
	m_ObjectPoolInstance = ObjectPool::Get();


	
}

void GameWorld::Update(float DeltaTime)
{
	/*mPlayer->Update(DeltaTime);
	mEnemy->Update(DeltaTime);*/

	for (int i = 0; i < mGameobjects.size(); i++)
	{
		if (mGameobjects[i]) {
			mGameobjects[i]->Update(DeltaTime);
		}
	}

	//if (IsGameobjectOutOfBounds(mPlayer)) {
	//	//std::cout << "Player is out of bounds" << std::endl;
	//}
	

	UpdateCollisions();

	mEnemySpawnTime -= DeltaTime;

	if (mEnemySpawnTime <= 0.0f) {
		mEnemySpawnTime = 5.0f;
		SpawnNewEnemy();
	}
	//UpdateArenaBounds(DeltaTime);
}

void GameWorld::Render(sf::RenderWindow* window)
{
	/*mPlayer->Draw(window);
	mEnemy->Draw(window);*/


	for (int i = 0; i < mGameobjects.size(); i++)
	{
		if (mGameobjects[i] != nullptr) {

			mGameobjects[i]->Draw(window);
		}
	}

	RenderArenaBounds();
}

void GameWorld::RenderArenaBounds()
{
	const float lineThickness = 16.0f;
	
	sf::RectangleShape arena(sf::Vector2f(arenaSize, arenaSize));

	arena.setOrigin(sf::Vector2f(arenaSize, arenaSize) * 0.5f);
	arena.setOutlineColor(sf::Color::Red);
	arena.setFillColor(sf::Color::Transparent);
	arena.setOutlineThickness(lineThickness);
	arena.setPosition(960.0f, 540.0f);
	

	mWindow->draw(arena);

}

bool GameWorld::IsGameobjectOutOfBounds(GameObject* gameobject)
{
	sf::FloatRect bounds = gameobject->GetTexture2D()->GetSprite()->getGlobalBounds();
		
	return ((bounds.left <= 500.0f) ||  // Left side of rectangle
			 (bounds.top <= 50.0f ) ||	// Top of the triangle
		(bounds.left + bounds.width) >= (1430.0f) || // Right side of the triangle
		(bounds.top + bounds.height) >= (950.0f));	// Bottom side of the triangle
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

void GameWorld::SpawnNewEnemy()
{
	const LLGP::Vector2f spawnPos(LLGP::FRandomRange(500.0f, 1430.f), LLGP::FRandomRange(50.0f, 950.0f));

	GameObject* newEnemy = nullptr;

	newEnemy = SpawnGameobject<Enemy>(GetResources().mEnemyTex);
	newEnemy->GetTransform()->SetPosition(spawnPos);

}

void GameWorld::UpdateArenaBounds(float dt)
{
	const float Damage = 1000.0f;
	
	for (GameObject* object : mGameobjects)
	{
		if (object != nullptr)
		{
			if (IsGameobjectOutOfBounds(object)) 
			{
				object->ApplyDamage(nullptr, Damage);
			}
		}
	}
}

// Delete player from the world and remove it from the list of gameobjects
void GameWorld::HandlePlayerDied(bool die)
{

	auto player = std::find(mGameobjects.begin(), mGameobjects.end(), mPlayer);
	mGameobjects.erase(player);
	delete mPlayer;
	mPlayer = nullptr;
}
