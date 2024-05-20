#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Event.h"
#include <iostream>
#include <map>

class FamilyMan;
class Player;
class Enemy;
class Grunts;
class Hulks;
class Brains;

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
	static const Resources& GetResources() { return mResources; }
	template <typename T> requires(std::derived_from <T,GameObject>)
		static void AddToGameobjects(T* gameobject) { mGameobjects.insert({gameobject->uuid,std::make_unique<T>(gameobject) });
}
	static LLGP::Vector2f const GetRandomPosInArena();
	static void RenderArenaBounds();
	static bool IsGameobjectOutOfBounds(GameObject* gameobject);
	template <typename T>
	static T* SpawnGameobject(sf::Texture* texture)
	{
		mGameobjects.insert(std::make_unique<T>(texture));
		//mGameobjects.emplace(std::make_unique<T>(texture));
		return static_cast<T*>(mGameobjects[mGameobjects.size() - 1]); // does not return the last element
	}
	static void DeleteObject(GameObject* object);
	static void UpdateCollisions();
	static sf::RenderWindow* mWindow;
	static void RemoveFromGameobject(GameObject* gameobject);
	static void SpawnNewEnemy();

	static void UpdateArenaBounds(float dt);
	
	static void HandlePlayerDied(bool die);

private:
	static Player* mPlayer;
	static Grunts* mGrunt;
	static Hulks* mHulk;
	static Brains* mBrain;
	static FamilyMan* mFamilyMan;
	static Resources mResources;
	static std::map<uint64_t,std::unique_ptr<GameObject>> mGameobjects;
	static float mEnemySpawnTime;
};


