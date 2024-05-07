#include "ObjectPool.h"
//#include "GameWorld.h"



//TODO create return function which finds pool, loops objects, checks equality between, set bool to true;
void ObjectPool::Start()
{
	for (int i = 0; i < objectsToPool.size(); i++)
	{
		/*m_Pools.push_back(Pool());*/
	

		for (int j= 0; j < objectsToPool[i].amountToPool; j++)
		{
			// Need a way to ignore the gameobject type so that we can use item.objectToPool
			GameObject* obj = objectsToPool[i].typeFactory();
			m_Pools[i]._Objects.push_back(obj);
		}
	}
}

void ObjectPool::Cleanup()
{
	for (Pool p : m_Pools)
	{
		for (GameObject* o : p._Objects)
		{
			delete(o);
		}
	}
}

GameObject* ObjectPool::GetPooledObject(std::string tag)
{
	// Loop through all the pools
	for (int i = 0; i < m_Pools.size(); i++)
	{
		if (m_Pools[i]._PoolTag == tag) 
		{
		
				// Loop through all the objects in the current iteration of the pool
				for (GameObject* o : m_Pools[i]._Objects)
				{
					if (o->GetIsActive())
					{
						o->SetActive(false);
						return o;
						//if (o.first)
						//{
						//	//TODO:figure this out
						//	o.first = false;	// Not active
						//	return o.second;
					}
				}

				//if here then pool exists but is all in use
				if (objectsToPool[i].expand)
				{
					//TODO: function this and other instances out
					GameObject* obj = objectsToPool[i].typeFactory();
					/*m_Pools[i]._Objects.insert(std::pair<bool, GameObject*>(false, obj));*/
					m_Pools[i]._Objects.push_back(obj);
					return obj;
				}

				//if here then pool exists, all are in use and we can't expand so error to developer
		}

			//if here the requested pool doesnt exist
	}
}

void ObjectPool::AddTypeToPool(std::function<GameObject* ()> infactory, int AmountToPool, bool Expand)
{
	if (std::find_if(objectsToPool.begin(), objectsToPool.end(), [infactory](ObjectPoolItem& b) {return b.typeFactory.target_type().hash_code() == infactory.target_type().hash_code(); }) == objectsToPool.end())
		{
			objectsToPool.push_back(ObjectPoolItem(infactory, AmountToPool, Expand));
		}
}

//GameObject* ObjectPool::GetPooledObject(std::string tag)
//{
// 	
//}

	

//void ObjectPool::AddTypeToPool(std::function<GameObject* ()> infactory, int AmountToPool, bool Expand)
//{
//	if (std::find_if(objectsToPool.begin(), objectsToPool.end(), [infactory](ObjectPoolItem &b) {return b.typeFactory.target_type().hash_code() == infactory.target_type().hash_code(); }) == objectsToPool.end())
//	{
//		objectsToPool.push_back(ObjectPoolItem(infactory, AmountToPool, Expand));
//	}
//}
