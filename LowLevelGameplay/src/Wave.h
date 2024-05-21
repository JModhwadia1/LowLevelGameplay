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
private:

	std::vector<Enemy*> mEnemiesInWave;
	std::vector<FamilyMan*> mFamilyManInWave;
};

