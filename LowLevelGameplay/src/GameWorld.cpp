#include "GameWorld.h"
#include "Vector2.h"
#include "Bullet.h"
#include "FamilyMan.h"
#include "Player.h"
#include "Enemy.h"
#include "ObjectPool.h"





float GameWorld::m_ArenaLeftPos = 500.0f;
float GameWorld::m_ArenaRightPos = 1430.0f;
float GameWorld::m_ArenaTopPos = 50.0f;
float GameWorld::m_ArenaBottomPos = 950.0f;
const float GameWorld::arenaSize = 900.0f;
float GameWorld::mEnemySpawnTime = 5.0f;


Player* GameWorld::mPlayer = nullptr;
Enemy* GameWorld::mEnemy = nullptr;
FamilyMan* GameWorld::mFamilyMan = nullptr;
std::vector<GameObject*> GameWorld::mGameobjects;
GameWorld::Resources GameWorld::mResources;
sf::RenderWindow* GameWorld::mWindow = nullptr;



//
//GameWorld::GameWorld(sf::RenderWindow* window)
//{
//	
//	Init();
//}


//
//GameWorld::~GameWorld()
//{
//	mPlayer->OnPlayerDied -= std::bind(&GameWorld::HandlePlayerDied, this, std::placeholders::_1);
//}

void GameWorld::Init(sf::RenderWindow* window)
{
	//world = this;
	mWindow = window;
	LoadTextures();
	ObjectPool::AddTypeToPool(std::bind([](){return new Bullet();}), 50,"Bullet");
	/*ObjectPool::GetPools().push_back(Pool(std::string("Bullet")));*/
	//Add more types
	ObjectPool::Start();

	std::cout << "1st pool object size:" << ObjectPool::GetPools()[0]._Objects.size();

	mPlayer = new Player();
	//mPlayer->OnPlayerDied += std::bind(&GameWorld::HandlePlayerDied, this, std::placeholders::_1);
	mEnemy = new Enemy(GetResources().mEnemyTex);
	mPlayer->GetTransform()->SetPosition(LLGP::Vector2f(960.0f, 540.0f));
//	mFamilyMan = /*SpawnGameobject<FamilyMan>(mResources.mMenTex);*/new FamilyMan();


	mGameobjects.push_back(mPlayer);
	//mGameobjects.push_back(mFamilyMan);
	mGameobjects.push_back(mEnemy);

	

	/*ObjectPool::objectsToPool.push_back(ObjectPoolItem());*/


	
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
		std::cout << "enforcers texture not loaded texture not loaded" << std::endl;
		return;
	}
}

void GameWorld::Update(float DeltaTime)
{
	

	for (int i = 0; i < mGameobjects.size(); i++)
	{
		if (mGameobjects[i]) {
			mGameobjects[i]->Update(DeltaTime);
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

void GameWorld::Render(sf::RenderWindow* window)
{

	mEnemy->Draw(window);


	for (int i = 0; i < mGameobjects.size(); i++)
	{
		if (mGameobjects[i] != nullptr) {

			mGameobjects[i]->Draw(window);
		}
	}

	RenderArenaBounds();
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

					LLGP::Vector2f collisionNormal = manifold.collisionNormal;
				
					collisionNormal.Normalise();
					LLGP::Vector2f relativeVelocity = b->GetRigidbody()->GetVelocity() - a->GetRigidbody()->GetVelocity();
					
					float dot = LLGP::Vector2f::Dot(collisionNormal, relativeVelocity);
					if (dot < 0.0f) {

						// Restitution - Between 0 and 1 for testing
						float e = 1.1f;
						// Get inverse mass of object A
						float invMassA = a->GetRigidbody()->GetInverseMass();
						// Get inverse mass of object B
						float invMassB = b->GetRigidbody()->GetInverseMass();
						// Calculate the inverse mass sum =  InvMassA + InvMass B
						float inverseMassSum = invMassA + invMassB;
						// Calculate total velocity
						float vj = -(1 + e) * dot;
						// Caluculate impulse
						float j = vj * (inverseMassSum);



						// Apply Impulse to object A
						a->GetTransform()->ChangePosition(invMassA * j * collisionNormal);
						b->GetTransform()->ChangePosition(-(invMassB * j * collisionNormal));
						
						std::cout << "COllision" << std::endl;


						

						manifold = CollisionManifold();
					}
					a->OnCollision(*b);
					b->OnCollision(*a);
				}
			}
		}
	}
}

void GameWorld::SpawnNewEnemy()
{
	const LLGP::Vector2f spawnPos(LLGP::FRandomRange(m_ArenaLeftPos, m_ArenaRightPos), LLGP::FRandomRange(m_ArenaTopPos, m_ArenaBottomPos));

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
