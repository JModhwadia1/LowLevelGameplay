#pragma once
#include "GameObject.h"
#include <vector>

class GameWorld;

// The Object Pool item
class ObjectPoolItem {
public:
	int amountToPool;
	GameObject objectToPool;
	bool expand = true;
};

struct Pool
{
	//TODO: add utility functions for getting next avail and returning
	std::vector<GameObject*> _Objects;

	GameObject* GetPooledObject(std::string tag);
};

class ObjectPool {
public:

	ObjectPool(const ObjectPool&) = delete;
	static ObjectPool& Get()
	{
		return Instance;
	}


	void Start();
	void SetWorld(GameWorld* world) { mWorld = world; }
	GameObject* GetPooledObject(std::string tag);

	std::vector<ObjectPoolItem> objectsToPool;
private:

	ObjectPool() {}
	std::vector<Pool> m_Pools;
	static ObjectPool Instance;
	
	GameWorld* mWorld;

};

ObjectPool ObjectPool::Instance;


