#pragma once
#include "GameObject.h"
#include <vector>

class GameWorld;

//https://stackoverflow.com/questions/26736405/can-objects-be-created-based-on-type-info

// The Object Pool item
class ObjectPoolItem {
public:
	/*ObjectPoolItem(int AMOUNTTOPOOL, GameObject OBJECTTOPOOL)*/
	int amountToPool;
	GameObject objectToPool;
	std::type_info typeToPool;
	bool expand = true;
};

struct Pool
{
	//TODO: add utility functions for getting next avail and returning
	std::vector<GameObject*> _Objects;

	GameObject* GetPooledObject(std::string tag);
};

extern class ObjectPool {
public:

	static void Start();
	static void SetWorld(GameWorld* world) { mWorld = world; }
	static GameObject* GetPooledObject(std::string tag);

	static std::vector<ObjectPoolItem> objectsToPool;
private:

	
	static std::vector<Pool> m_Pools;
	
	static GameWorld* mWorld;

};




