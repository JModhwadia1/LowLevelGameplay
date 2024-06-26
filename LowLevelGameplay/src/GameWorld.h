#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Event.h"
#include <iostream>
#include <unordered_map>
#include <SFML/Audio.hpp>

class FamilyMan;
class Player;
class Enemy;
class Grunts;
class Hulks;
class Brains;
class GameManager;
class UI;


class GameWorld
{
public:

	struct Resources {
		sf::Texture* mPlayerTex;
		sf::Texture* mEnemyTex;
		sf::Texture* mBulletTex;
		sf::Texture* mMenTex;
		sf::Texture* mWomenTex;
		sf::Texture* mBoyTex;
		
		// Enemies Textures
		sf::Texture* mGruntsTex;
		sf::Texture* mHulksTex;
		sf::Texture* mBrainsTex;
		sf::Texture* mSpheroidsTex;
		sf::Texture* mEnforcersTex;
		sf::Texture* mTanksTex;

		// Font
		sf::Font mMainFont;

		// Sounds
		//sf::SoundBuffer mBulletBuffer;


	};

public:

	static const float arenaSize;

	// Positions of each side of the area (Note: does not affect arena visually)
	static float m_ArenaLeftPos;
	static float m_ArenaRightPos;
	static float m_ArenaTopPos;
	static float m_ArenaBottomPos;
	static void Init(sf::RenderWindow* window);
	static void LoadTextures();
	static void Update(float DeltaTime);
	static void FixedUpdate(float FixedDeltaTime);
	static void Render(sf::RenderWindow* window);
	static Player* GetPlayer()  { if (mPlayer != nullptr) { return mPlayer; } }
	static  Resources& GetResources() { return mResources; }
	

	static LLGP::Vector2f const GetRandomPosInArena();
	static void RenderArenaBounds();
	static bool IsGameobjectOutOfBounds(GameObject* gameobject);
	template <typename T>
	static T* SpawnGameobject()
	{
		
		std::unique_ptr<T> temp = std::make_unique<T>();
		uint64_t tempUUID = temp->uuid;
		mGameobjects.insert( {tempUUID, std::move(temp)} );
		//mGameobjects.emplace(std::make_unique<T>(texture));
		return static_cast<T*>(mGameobjects[tempUUID].get()); 
	}
	static void DeleteObject(GameObject* object);
	static void UpdateCollisions();
	static sf::RenderWindow* mWindow;
	static void RemoveFromGameobject(GameObject* gameobject);
	static void SpawnNewEnemy();

	static void UpdateArenaBounds(float dt);
	static void AddToCollisionGameobjects(GameObject* gameobject) { mCollisionGameobjects.push_back(gameobject); }
	static void HandlePlayerDied(bool die);
	static void RemovePlayer();
	static void ShutDown();

private:
	static Player* mPlayer;
	static Grunts* mGrunt;
	static Hulks* mHulk;
	static Brains* mBrain;
	static FamilyMan* mFamilyMan;
	static Resources mResources;
	static std::unordered_map<uint64_t,std::unique_ptr<GameObject>> mGameobjects;
	static float mEnemySpawnTime;

	static std::vector<GameObject*> mCollisionGameobjects;
	static GameManager* mGameManager;
	static UI* mUI;

	static sf::Text mPlayerPoints;
};


