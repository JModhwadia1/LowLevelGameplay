#pragma once
#include "Event.h"
#include "Vector2.h"
#include "SFML/Graphics.hpp"



static class InputManager
{
	
public:
	static LLGP::Event<LLGP::Vector2f> OnMovePerformed;
	//static LLGP::Event<LLGP::Vector2f> OnMoveCancelled;

	static void HandleInputs();
private:
	static LLGP::Vector2f MoveInputObserver;

};

