#include "UI.h"
#include "GameManager.h"
#include "GameWorld.h"
#include <string>
UI::UI(GameManager* manager) 
{
	mGameManager = manager;
}

void UI::Init() 
{
	
	mGameManager->OnPlayerPointUpdated.AddListener(this, std::bind(&UI::HandlePlayerPointsUpdated, this, std::placeholders::_1));
	mGameManager->OnPlayerLivesUpdated.AddListener(this, std::bind(&UI::HandlePlayerLivesUpdated, this, std::placeholders::_1));

	mPointsAmountText.setFont(GameWorld::GetResources().mMainFont);
	mPointsAmountText.setCharacterSize(32);
	mPointsAmountText.setStyle(sf::Text::Bold);

	mLivesAmountText.setFont(GameWorld::GetResources().mMainFont);
	mLivesAmountText.setCharacterSize(32);
	mLivesAmountText.setStyle(sf::Text::Bold);

	mPointsAmountText.setString("0");
	mLivesAmountText.setString(std::to_string(mGameManager->GetLives()));

	mLivesText.setFont(GameWorld::GetResources().mMainFont);
	mLivesText.setCharacterSize(32);
	mLivesText.setStyle(sf::Text::Bold);
	mLivesText.setString("Lives: ");

	mPointsText.setFont(GameWorld::GetResources().mMainFont);
	mPointsText.setCharacterSize(32);
	mPointsText.setStyle(sf::Text::Bold);
	mPointsText.setString("Points: ");
	
}

void UI::HandlePlayerPointsUpdated(int points) {
	
	mPointsAmountText.setString(std::to_string(points));
}
void UI::HandlePlayerLivesUpdated(int lives) 
{
	mLivesAmountText.setString(std::to_string(lives));
}
void UI::Draw(sf::RenderWindow* window) 
{
	
	sf::Vector2f vpSize = window->getView().getSize();


	mPointsAmountText.setPosition(800.0f,20.0f);
	mPointsText.setPosition(700.0f, 20.0f);
	mLivesAmountText.setPosition(600.0f, 20.0f);
	mLivesText.setPosition(500.0f, 20.0f);
	window->draw(mPointsAmountText);
	window->draw(mLivesAmountText);
	window->draw(mLivesText);
	window->draw(mPointsText);
}
UI::~UI() 
{
	mGameManager->OnPlayerPointUpdated.RemoveListener(this, std::bind(&UI::HandlePlayerPointsUpdated, this, std::placeholders::_1));
	mGameManager->OnPlayerLivesUpdated.RemoveListener(this, std::bind(&UI::HandlePlayerLivesUpdated, this, std::placeholders::_1));
	mGameManager = nullptr;
}
