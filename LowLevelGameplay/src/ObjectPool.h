#pragma once
#include "GameObject.h"
#include <vector>
#include "Factory.h"
#include <functional>
#include <unordered_map>
class GameWorld;

//https://stackoverflow.com/questions/26736405/can-objects-be-created-based-on-type-info

// The Object Pool item
class ObjectPoolItem {
public:
	ObjectPoolItem(std::function<GameObject* ()>infactory, int AmountToPool, bool Expand = true) : typeFactory(infactory), amountToPool(AmountToPool), expand(Expand) {}
	std::function<GameObject* ()> typeFactory;
	int amountToPool;
	bool expand = true;
};

struct Pool
{
	std::string _PoolTag;
	//TODO: add utility functions for getting next avail and returning
	std::unordered_map<bool,GameObject*> _Objects;

	GameObject* GetPooledObject(std::string tag);
};

extern class ObjectPool {
public:

	static void Start();
	static void Cleanup();
	static void SetWorld(GameWorld* world) { mWorld = world; }
	static GameObject* GetPooledObject(std::string tag);
	static void AddTypeToPool(std::function<GameObject* ()> infactory,int AmountToPool, bool Expand = true);
	static std::vector<ObjectPoolItem> objectsToPool;
private:

	
	static std::vector<Pool> m_Pools;
	
	static GameWorld* mWorld;

};




