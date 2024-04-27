#include "ObjectPool.h"
#include "GameWorld.h"



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

	// Loop through all the pools
	for (int i = 0; i <m_Pools.size(); i++)
	{
		// Loop through all the objects in the current iteration of the pool
		for (int  j= 0;  j < m_Pools[i]._Objects.size(); j++)
		{
			// Check if the current object has the same tag 
			if (m_Pools[i]._Objects[j]->CompareTag(tag)) {

				// if the tag matches  the gameobjects tag then return it
				return m_Pools[i].GetPooledObject(tag);
			}
		}
	}
}

GameObject* Pool::GetPooledObject(std::string tag)
{
	for (int i = 0; i < _Objects.size(); i++)
	{
		if (_Objects[i]->CompareTag(tag))
		{

			return _Objects[i];
		}
	}
}
