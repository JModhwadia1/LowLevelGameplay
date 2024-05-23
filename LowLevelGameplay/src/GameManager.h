#pragma once
#include "Event.h"
#include "SFML/Graphics.hpp"
class Player;
class Grunt;
class Family;
class FamilyMan;
class Wave;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Init();
	void Update(float dt);
	void HandleEnemyDied(bool die, int PointsToGive);
	void BindToGruntsDiedEvent(Wave* wave);
	void HandlePlayerDied(bool die);

	Wave* wave1;

	LLGP::Event<int> OnPlayerPointUpdated;
	LLGP::Event<int> OnPlayerLivesUpdated;
	int GetLives() { return mPlayerLives; }
	std::vector<Wave*> waves;

	void ClearWave(Wave* wave);
private:
	int mPlayerLives = 3;
	int mPlayerPoints = 0;
	int wavesCompleted = 0;
	
};


