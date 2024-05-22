#pragma once
#include <SFML/Graphics.hpp>

class GameManager;

class UI 
{
public:
	UI(GameManager* manager);
	void Init();
	void HandlePlayerPointsUpdated(int points);
	void HandlePlayerLivesUpdated(int lives);
	void Draw(sf::RenderWindow* window);
	~UI();
private:
	GameManager* mGameManager;
	sf::Text mPointsAmountText;
	sf::Text mLivesAmountText;
	sf::Text mLivesText;
	sf::Text mPointsText;
};
