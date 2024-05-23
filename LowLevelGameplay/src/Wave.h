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
	void HandleGruntsDied(bool died, int points);
	
	LLGP::Event<Wave*> OnAllGruntsSpawned;
	LLGP::Event<Wave*> OnWaveComplete;

	bool shouldStartSpawningEnemies;
private:
	int _numberOfGruntsToSpawn; int _numberOfHulksToSpawn; int _numberOfFamilyMenToSpawn; int _numberofBrainsToSpawn;
	int _numberOfGruntsInWave = 0; int _numberOfHulksInWave = 0; int _numberOfFamilyMenInWave = 0; int _numberofBrainsInWave = 0;

	int _numberOfGruntsDied = 0;
	std::vector<FamilyMan*> mFamilyManInWave;
	float spawnDelay = 0.1f;
	std::vector<Grunts*> mGruntsInWave;
};

