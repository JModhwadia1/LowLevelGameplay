#pragma once
#include "Event.h"
#include "SFML/Graphics.hpp"



class InputManager
{
	LLGP::Event < sf::Keyboard::Key> onPressed;
	
	InputManager();

	void HandleInputs();
};

