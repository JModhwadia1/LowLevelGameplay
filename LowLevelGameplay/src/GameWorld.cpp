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
std::map<uint64_t, std::unique_ptr<GameObject>> GameWorld::mGameobjects;
GameWorld::Resources GameWorld::mResources;
sf::RenderWindow* GameWorld::mWindow = nullptr;





void GameWorld::Init(sf::RenderWindow* window)
{
	//world = this;
	mWindow = window;
	LoadTextures();
	ObjectPool::AddTypeToPool(std::bind([](){return new Bullet();}), 1000,"Bullet");
	/*ObjectPool::GetPools().push_back(Pool(std::string("Bullet")));*/
	//Add more types
	ObjectPool::Start();

	std::cout << "1st pool object size:" << ObjectPool::GetPools()[0]._Objects.size();

	mPlayer = SpawnGameobject<Player>(mResources.mPlayerTex);

	mGrunt = new Grunts(mResources.mGruntsTex);
	mHulk = new Hulks(mResources.mHulksTex);
	mHulk->GetTransform()->SetPosition(GetRandomPosInArena());
	mBrain = new Brains(mResources.mBrainsTex);
	mBrain->GetTransform()->SetPosition(LLGP::Vector2f(100.0f, 400.0f));
	mGrunt->GetTransform()->SetPosition(LLGP::Vector2f(200.0f, 540.0f));
	mPlayer->GetTransform()->SetPosition(LLGP::Vector2f(960.0f, 540.0f));
//	mFamilyMan = /*SpawnGameobject<FamilyMan>(mResources.mMenTex);*/new FamilyMan();




	

	


	
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
}

void GameWorld::Update(float DeltaTime)
{
	
	
	for (int i = 0; i < mGameobjects.size(); i++)
	{
		if (mGameobjects[i].get()) {
			mGameobjects[i].get()->Update(DeltaTime);
		}
	}

	mEnemySpawnTime -= DeltaTime;

	if (mEnemySpawnTime <= 0.0f)
	{
		mEnemySpawnTime = 5.0f;
		//SpawnNewEnemy();
		
		
	
		
	}
	//UpdateArenaBounds(DeltaTime);
}


void GameWorld::FixedUpdate(float FixedDeltaTime)
{
	
	for (int i = 0; i < mGameobjects.size(); i++)
	{
		if (mGameobjects[i]) {
			
			mGameobjects[i]->FixedUpdate(FixedDeltaTime);
		}
	}
}
void GameWorld::Render(sf::RenderWindow* window)
{



	for (int i = 0; i < mGameobjects.size(); i++)
	{
		if (mGameobjects[i] != nullptr) {

			mGameobjects[i]->Draw(window);
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
	std::erase_if(mGameobjects, [object](std::pair<uint64_t, std::unique_ptr<GameObject>>check) {return object->uuid == check.first; });
}

void GameWorld::UpdateCollisions()
{
	CollisionManifold manifold;
	// change to int
	//for (int it = mGameobjects.begin(); it < mGameobjects.end(); ++it)
	//{
	//	for (auto it2 = it + 1; it2 < mGameobjects.end(); ++it2)
	//	{
	//		GameObject* a = *it;
	//		GameObject* b = *it2;
	//		

	//		if (a != nullptr && b != nullptr)
	//		{
	//			if (a->IsCollideable() && b->IsCollideable() && a->GetCollider()->CollidesWith(*b->GetCollider(), manifold))
	//			{
	//				
	//				a->OnCollision(*b);
	//				b->OnCollision(*a);
	//			}
	//		}
	//	}
	//}


	for (int i = 0; i < mGameobjects.size(); i++)
	{
		for (int j = i + 1; j < mGameobjects.size(); j++)
		{
			
			if(mGameobjects[i].get()->IsCollideable() && mGameobjects[j].get()->IsCollideable() && 
				mGameobjects[i].get()->GetCollider()->CollidesWith(*mGameobjects[j].get()->GetCollider(), manifold)) 
			{
				mGameobjects[i].get()->OnCollision(*mGameobjects[j].get());
				mGameobjects[j].get()->OnCollision(*mGameobjects[i].get());
			}
		}
	}
}

void GameWorld::RemoveFromGameobject(GameObject* gameobject)
{
	/*std::vector<GameObject*>::iterator position = std::find(mGameobjects.begin(), mGameobjects.end(), gameobject);
	mGameobjects.erase(position);*/

}

void GameWorld::SpawnNewEnemy()
{
	const LLGP::Vector2f spawnPos(LLGP::FRandomRange(m_ArenaLeftPos, m_ArenaRightPos), LLGP::FRandomRange(m_ArenaTopPos, m_ArenaBottomPos));

	//std::uniqueGameObject* newEnemy = nullptr;

	//newEnemy = SpawnGameobject<Enemy>(GetResources().mEnemyTex);
	//newEnemy->GetTransform()->SetPosition(spawnPos);

	SpawnGameobject<Enemy>(mResources.mEnemyTex);

}

void GameWorld::UpdateArenaBounds(float dt)
{
	const float Damage = 1000.0f;
	
	//for (std::unique_ptr<GameObject> object : mGameobjects.begin())
	//{
	//	if (object != nullptr)
	//	{
	//		if (IsGameobjectOutOfBounds(object)) 
	//		{
	//			object->ApplyDamage(nullptr, Damage);
	//		}
	//	}
	//}
		
	for (int i = 0; i < mGameobjects.size(); i++)
	{
		if (IsGameobjectOutOfBounds(mGameobjects[i].get())) {
			mGameobjects[i].get()->ApplyDamage(nullptr, Damage);
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
