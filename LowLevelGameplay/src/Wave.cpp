#include "Wave.h"
#include "ObjectPool.h"

#include "Enemy.h"
Wave::Wave(int numberOfEnemies)
{
	for (int i = 0; i <= numberOfEnemies; i++)
	{
		Enemy* enemy = ObjectPool::GetPooledObjectAsType<Enemy>("Enemy");
		mEnemiesInWave.push_back(enemy);
	}
}

Wave::~Wave()
{
	
}
