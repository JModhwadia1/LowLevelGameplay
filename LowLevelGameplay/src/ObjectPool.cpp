#include "ObjectPool.h"
#include "GameWorld.h"

ObjectPool::ObjectPool(GameWorld* world)
{
	mWorld = world;
}

ObjectPool::~ObjectPool()
{
}

void ObjectPool::Start()
{

	/*mGameobjectsPool = std::list<GameObject>();*/
	
	for (int i = 0; i < objectsToPool.size(); i++)
	{
		m_Pools.push_back(Pool());

		for (int j= 0; j < objectsToPool[i].amountToPool; j++)
		{
			// Need a way to ignore the gameobject type so that we can use item.objectToPool
			GameObject* obj = mWorld->SpawnGameobject<GameObject>(mWorld->GetResources().mPlayerTex);	
			m_Pools[i]._Objects.push_back(obj);
		}
	}
}

GameObject* ObjectPool::GetPooledObject(std::string tag)
{

	
	// https://stackoverflow.com/questions/22269435/how-to-iterate-through-a-list-of-objects-in-c -- for loop
	//std::list<GameObject>::iterator it;
	//for ( it = mGameobjectsPool.begin(); it != mGameobjectsPool.end(); ++it)
	//{

	//	if (it->GetName() == tag) {
	//		return;
	//	}
	//}

	for (int i = 0; i < m_Pools.size(); i++)
	{
		// name of the pool 
		if (m_Pools[i].GetName() == tag) {

			// Need a way to return the gameobject
			for (int i = 0; i < m_Pools[i]; i++)
			{

			}
		}
		return nullptr;
	}
}
