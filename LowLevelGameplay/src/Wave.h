#pragma once
#include <iostream>
#include <vector>
#include "Event.h"
using namespace std;

class Enemy;
class FamilyMan;
class Grunts;
class Wave
{

public:
	Wave(int numberOfGrunts, int numberOfHulks, int numberOfFamilyMen, int numberofBrains);
	~Wave();
	void ClearWave();
	void SpawnEnemies(float dt);
	void ReduceGruntCount(bool die, int pointsTogive);
	std::vector<Grunts*> GetGruntsInWave() { return mGruntsInWave; }
	
	LLGP::Event<> OnAllGruntsSpawned;
	LLGP::Event<> OnWaveComplete;
private:
	int _numberOfGruntsToSpawn; int _numberOfHulksToSpawn; int _numberOfFamilyMenToSpawn; int _numberofBrainsToSpawn;
	int _numberOfGruntsInWave = 0; int _numberOfHulksInWave = 0; int _numberOfFamilyMenInWave = 0; int _numberofBrainsInWave = 0;
	std::vector<FamilyMan*> mFamilyManInWave;
	float spawnDelay = 1.0f;
	std::vector<Grunts*> mGruntsInWave;
};

