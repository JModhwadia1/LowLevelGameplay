//#include "ObjectPool.h"
//#include "GameWorld.h"
//
//ObjectPool::ObjectPool(GameWorld* world)
//{
//	mWorld = world;
//}
//
//ObjectPool::~ObjectPool()
//{
//}
//
//void ObjectPool::Start()
//{
//
//	/*mGameobjectsPool = std::list<GameObject>();*/
//	
//
//	for (int i = 0; i < listOfPools.size(); i++)
//	{
//		ObjectPoolItem item;
//		for (int j= 0; j < item.amountToPool; j++)
//		{
//			// Need a way to ignore the gameobject type so that we can use item.objectToPool
//			GameObject* obj = mWorld->SpawnGameobject<GameObject>(mWorld->GetResources().mPlayerTex);	
//			mGameobjectsPool.push_back(*obj);
//		}
//	}
//}
//
//GameObject* ObjectPool::GetPooledObject(std::string tag)
//{
//
//	
//	// https://stackoverflow.com/questions/22269435/how-to-iterate-through-a-list-of-objects-in-c -- for loop
//	//std::list<GameObject>::iterator it;
//	//for ( it = mGameobjectsPool.begin(); it != mGameobjectsPool.end(); ++it)
//	//{
//
//	//	if (it->GetName() == tag) {
//	//		return;
//	//	}
//	//}
//
//	for (int i = 0; i < mGameobjectsPool.size(); i++)
//	{
//		if (mGameobjectsPool[i].GetName() == tag) {
//
//			// Need a way to return the gameobject
//		//	return mGameobjectsPool[i];
//		}
//		return nullptr;
//	}
//}
