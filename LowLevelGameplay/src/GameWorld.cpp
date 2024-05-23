#include "GameWorld.h"
#include "Vector2.h"
#include "Bullet.h"
#include "FamilyMan.h"
#include "Player.h"
#include "Grunts.h"
#include "Hulks.h"
#include <algorithm>
#include "ObjectPool.h"
#include "Brains.h"
#include "GameManager.h"
#include "UI.h"




float GameWorld::m_ArenaLeftPos = 500.0f;
float GameWorld::m_ArenaRightPos = 1430.0f;
float GameWorld::m_ArenaTopPos = 50.0f;
float GameWorld::m_ArenaBottomPos = 950.0f;
const float GameWorld::arenaSize = 900.0f;
float GameWorld::mEnemySpawnTime = 5.0f;


Player* GameWorld::mPlayer = nullptr;
Grunts* GameWorld::mGrunt = nullptr;
Hulks* GameWorld::mHulk = nullptr;
Brains* GameWorld::mBrain = nullptr;
FamilyMan* GameWorld::mFamilyMan = nullptr;
std::unordered_map<uint64_t, std::unique_ptr<GameObject>> GameWorld::mGameobjects;
GameWorld::Resources GameWorld::mResources;
sf::RenderWindow* GameWorld::mWindow = nullptr;
std::vector<GameObject*> GameWorld::mCollisionGameobjects;
GameManager* GameWorld::mGameManager= nullptr;
UI* GameWorld::mUI = nullptr;




void GameWorld::Init(sf::RenderWindow* window)
{
	//world = this;
	mWindow = window;
	LoadTextures();
	mPlayer = SpawnGameobject<Player>();
	AddToCollisionGameobjects(mPlayer);
	ObjectPool::AddTypeToPool(std::bind([](){return GameWorld::SpawnGameobject<Bullet>();}), 10,"Bullet");
	ObjectPool::AddTypeToPool(std::bind([](){return GameWorld::SpawnGameobject<Grunts>();}), 1000,"Grunts");
	//Add more types
	ObjectPool::Start();

	

	// Spawn player

	// Spawn grunt
//	mGrunt = ObjectPool::GetPooledObjectAsType<Grunts>("Grunts");

	//mGrunt->GetTransform()->SetPosition(LLGP::Vector2f(200.0f, 540.0f));
	mPlayer->GetTransform()->SetPosition(LLGP::Vector2f(960.0f, 540.0f));

	mGameManager = new GameManager();
	mGameManager->Init();

	mUI = new UI(mGameManager);

	mUI->Init();
	
}

void GameWorld::LoadTextures()
{
	//mPlayerTex = new sf::Texture();
	//mEnemyTex = new sf::Texture();
	mResources.mPlayerTex = new sf::Texture();
	mResources.mBulletTex = new sf::Texture();
	mResources.mEnemyTex = new sf::Texture();
	mResources.mMenTex = new sf::Texture();
	mResources.mWomenTex = new sf::Texture();
	mResources.mBoyTex = new sf::Texture();

	// Enemies Textures
	mResources.mGruntsTex = new sf::Texture();
	mResources.mHulksTex = new sf::Texture();
	mResources.mBrainsTex = new sf::Texture();
	mResources.mSpheroidsTex = new sf::Texture();
	mResources.mEnforcersTex = new sf::Texture();
	mResources.mTanksTex = new sf::Texture();

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

	if (!mResources.mMenTex->loadFromFile("Textures/Family.png", sf::IntRect(1, 13, 5, 12)))
	{
		std::cout << "Men texture not loaded" << std::endl;
		return;
	}

	if (!mResources.mWomenTex->loadFromFile("Textures/Family.png", sf::IntRect(0, 41, 6, 13)))
	{
		std::cout << "Women texture not loaded" << std::endl;
		return;
	}

	if (!mResources.mBoyTex->loadFromFile("Textures/Family.png", sf::IntRect(0, 85, 4, 10)))
	{
		std::cout << "Boy texture not loaded" << std::endl;
		return;
	}

	if (!mResources.mGruntsTex->loadFromFile("Textures/enemies.png", sf::IntRect(0, 0, 9, 12)))
	{
		std::cout << "grunts texture not loaded texture not loaded" << std::endl;
		return;
	}

	if (!mResources.mHulksTex->loadFromFile("Textures/enemies.png", sf::IntRect(0, 14, 10, 14)))
	{
		std::cout << "hulks texture not loaded texture not loaded" << std::endl;
		return;
	}

	if (!mResources.mBrainsTex->loadFromFile("Textures/enemies.png", sf::IntRect(0, 142, 12, 15)))
	{
		std::cout << "brains texture not loaded texture not loaded" << std::endl;
		return;
	}

	if (!mResources.mSpheroidsTex->loadFromFile("Textures/enemies.png", sf::IntRect(0, 63, 1, 15)))
	{
		std::cout << "spheroids texture not loaded texture not loaded" << std::endl;
		return;
	}

	if (!mResources.mEnforcersTex->loadFromFile("Textures/enemies.png", sf::IntRect(0, 79, 3, 11)))
	{
		std::cout << "enforcers texture not loaded texture not loaded" << std::endl;
		return;
	}

	if (!mResources.mTanksTex->loadFromFile("Textures/enemies.png", sf::IntRect(0, 117, 6, 16)))
	{
		std::cout << "tanks  texture not loaded texture not loaded" << std::endl;
		return;
	}

	//if (!mResources.mMainFont->loadFromFile("Textures/enemies.png")
	//{

	//}

	if (!mResources.mMainFont.loadFromFile("Textures/American Captain.ttf")) {
		std::cout << "FONT NOT LOADED" << std::endl;
		return;
	}

	/*if (!mResources.mBulletBuffer.loadFromFile("Textures/Bullet.wav")) {
		std::cout << "bullet not loaded" << std::endl;
		return;
	}*/
}

void GameWorld::Update(float DeltaTime)
{
	
	// Fixes memory leak
	std::unordered_map<uint64_t, std::unique_ptr<GameObject>>::iterator l_Obj_it;
	for (l_Obj_it = mGameobjects.begin(); l_Obj_it != mGameobjects.end(); l_Obj_it++) 
	{
		if (l_Obj_it->second->GetIsActive()) {
			l_Obj_it->second->Update(DeltaTime);
		}
	}
	mGameManager->Update(DeltaTime);
	
	UpdateArenaBounds(DeltaTime);
}


void GameWorld::FixedUpdate(float FixedDeltaTime)
{
	// Fixes memory leak
	std::unordered_map<uint64_t, std::unique_ptr<GameObject>>::iterator l_Obj_it;
	for (l_Obj_it = mGameobjects.begin(); l_Obj_it != mGameobjects.end(); l_Obj_it++)
	{
		if (l_Obj_it->second->GetIsActive()) {
			l_Obj_it->second->FixedUpdate(FixedDeltaTime);
		}

	}
	
}
void GameWorld::Render(sf::RenderWindow* window)
{

	mUI->Draw(window);
	// Fixes memory leak
	std::unordered_map<uint64_t, std::unique_ptr<GameObject>>::iterator l_Obj_it;
	for (l_Obj_it = mGameobjects.begin(); l_Obj_it != mGameobjects.end(); l_Obj_it++)
	{
		if (l_Obj_it->second->GetIsActive()) {
			l_Obj_it->second->Draw(window);
		}
	}
	

	RenderArenaBounds();
}

LLGP::Vector2f const GameWorld::GetRandomPosInArena()
{
	const LLGP::Vector2f randomPos(LLGP::FRandomRange(m_ArenaLeftPos, m_ArenaRightPos), LLGP::FRandomRange(m_ArenaTopPos, m_ArenaBottomPos));
	return randomPos;
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
		
	return ((bounds.left <= m_ArenaLeftPos) ||  // Left side of rectangle
			 (bounds.top <= m_ArenaTopPos) ||	// Top of the triangle
		(bounds.left + bounds.width) >= (m_ArenaRightPos) || // Right side of the triangle
		(bounds.top + bounds.height) >= (m_ArenaBottomPos));	// Bottom side of the triangle
}


void GameWorld::DeleteObject(GameObject* object)
{
	std::erase_if(mGameobjects, [object](const auto& check) {auto const& [key, value] = check;  return object->uuid == key; });
}

void GameWorld::UpdateCollisions()
{
	CollisionManifold manifold;


	for (auto it = mCollisionGameobjects.begin(); it < mCollisionGameobjects.end(); ++it)
	{

		for (auto it2 = it + 1; it2 < mCollisionGameobjects.end(); ++it2)
		{
			GameObject* a = *it;
			GameObject* b = *it2;


			if (a != nullptr && b != nullptr && a->GetIsActive() && b->GetIsActive())
			{
				if (a->IsCollideable() && b->IsCollideable() && a->GetCollider()->CollidesWith(*b->GetCollider(), manifold))
				{
					if (a->GetIsActive() && b->GetIsActive()) {
						a->OnCollision(*b);
						b->OnCollision(*a);
					}
					
				}
			}
		}


	}
	

}


void GameWorld::SpawnNewEnemy()
{
	const LLGP::Vector2f spawnPos(LLGP::FRandomRange(m_ArenaLeftPos, m_ArenaRightPos), LLGP::FRandomRange(m_ArenaTopPos, m_ArenaBottomPos));

	//std::uniqueGameObject* newEnemy = nullptr;

	//newEnemy = SpawnGameobject<Enemy>(GetResources().mEnemyTex);
	//newEnemy->GetTransform()->SetPosition(spawnPos);

	//SpawnGameobject<Enemy>();

}

void GameWorld::UpdateArenaBounds(float dt)
{
	const float Damage = 1000.0f;
			
	// check to see if player is out of bounds
	if (IsGameobjectOutOfBounds(mPlayer)) {
		mPlayer->ApplyDamage(nullptr, Damage);
	}
}




void GameWorld::RemovePlayer() {
	if (mGameManager->GetLives() <= 0)
	{
		mPlayer->SetActive(false);
	}
}


