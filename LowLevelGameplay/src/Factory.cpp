#include "Factory.h"
#include "GameWorld.h"
#include "Bullet.h"
#include "Enemy.h"

GameObject* BulletFactory::Create()
{
	return new Bullet(mWorld, mWorld->GetResources().mBulletTex);
}

GameObject* EnemyFactory::Create()
{
	return new Enemy(mWorld, mWorld->GetResources().mEnemyTex);
}
