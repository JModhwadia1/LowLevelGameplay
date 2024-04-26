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
};

class ObjectPool {
public:

	ObjectPool(GameWorld* world );
	~ObjectPool();

	void Start();
	GameObject* GetPooledObject(std::string tag);
	static ObjectPool sharedInstance;

	std::vector<ObjectPoolItem> objectsToPool;
private:
	std::vector<Pool> m_Pools;
	
	GameWorld* mWorld;

};
