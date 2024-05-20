#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Enemy;

class Wave
{
	
public:
	Wave(int numberOfEnemies);
	~Wave();
private:

	std::vector<Enemy*> mEnemiesInWave;
};

