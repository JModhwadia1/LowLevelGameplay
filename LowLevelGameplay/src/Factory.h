//#pragma once
//#include <string>
//#include <list>
//#include <unordered_map>
//#include <iostream>
////#include "Bullet.h"
//
//class GameWorld;
//class Bullet;
//class Enemy;
//
//class GameobjectFactory 
//{
//public:
//	virtual ~GameobjectFactory() {};
//	virtual GameObject* Create() = 0;
//};
//
//class GameobjectTypeFactory 
//{
//public:
//	// add to the factories list
//	void RegisterFactory(std::string gameobjectType, GameobjectFactory* gameobjectFactory) 
//	{
//		_factories.insert(std::pair<std::string, GameobjectFactory*>(gameobjectType, gameobjectFactory));
//	}
//	// Create the game object
//	GameObject* Create(std::string gameobjectType) 
//	{
//		return _factories.at(gameobjectType)->Create();
//	}
//
//	// return a list of all the types of items 
//	std::list<std::string> GetTypes() 
//	{
//		std::list<std::string> result;
//		for (auto& item : _factories) 
//		{
//			result.push_back(item.first);
//		}
//		return result;
//	}
//	
//private:
//	// Store the factories 
//	std::unordered_map<std::string, GameobjectFactory*> _factories;
//
//};
//
//class BulletFactory : public GameobjectFactory {
//public:
//	GameWorld* mWorld;
//
//	virtual GameObject* Create();
//};
//
//class EnemyFactory : public GameobjectFactory {
//public:
//	GameWorld* mWorld;
//
//	virtual GameObject* Create();
//};
//
//
