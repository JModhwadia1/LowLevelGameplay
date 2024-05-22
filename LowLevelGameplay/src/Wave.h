#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Enemy;
class FamilyMan;
class Wave
{
	
public:
	Wave(int numberOfGrunts, int numberOfHulks, int numberOfFamilyMen, int numberofBrains);
	~Wave();
	void ClearWave();
	void SpawnEnemies(float dt);
private:
	int _numberOfGruntsToSpawn; int _numberOfHulksToSpawn; int _numberOfFamilyMenToSpawn; int _numberofBrainsToSpawn;
	int _numberOfGruntsInWave = 0; int _numberOfHulksInWave = 0; int _numberOfFamilyMenInWave = 0; int _numberofBrainsInWave = 0;
	std::vector<Enemy*> mEnemiesInWave;
	std::vector<FamilyMan*> mFamilyManInWave;
	float spawnDelay = 0.5f;
};

