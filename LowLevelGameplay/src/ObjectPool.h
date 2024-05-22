#pragma once
#include "GameObject.h"
#include <vector>
#include "Factory.h"
#include <functional>
#include <unordered_map>




// The Object Pool item
class ObjectPoolItem {
public:
	ObjectPoolItem(std::function<GameObject* ()>infactory, int AmountToPool, std::string Name,bool Expand = true) : typeFactory(infactory), amountToPool(AmountToPool), expand(Expand),name(Name) {}
	std::function<GameObject* ()> typeFactory;
	int amountToPool;
	bool expand = true;
	std::string name;
};

struct Pool
{
	Pool(std::string poolTag) { _PoolTag = poolTag; }
	std::string _PoolTag;
	//TODO: add utility functions for getting next avail and returning
	std::vector<GameObject*> _Objects;
};

class ObjectPool {
public:

	static void Start();
	static void Cleanup();
	static GameObject* GetPooledObject(std::string tag);
	template <typename T> requires std::derived_from<T,GameObject>
	static T* GetPooledObjectAsType(std::string tag) {
		return dynamic_cast<T*>(ObjectPool::GetPooledObject(tag));
	}
	static void AddTypeToPool(std::function<GameObject* ()> infactory,int AmountToPool,std::string Name, bool Expand = true);
	static std::vector<ObjectPoolItem> objectsToPool;
	static std::vector<Pool> GetPools() { return m_Pools; }
private:

	
	static std::vector<Pool> m_Pools;
	

};







