#include "InputManager.h"

void InputManager::HandleInputs()
{
	LLGP::Vector2f moveinput(
	sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A), 
		sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)
	);


	OnMovePerformed(moveinput);
	/*if (moveinput != MoveInputObserver)
	{
		if (moveinput == LLGP::Vector2f::zero)
		{
			OnMoveCancelled(moveinput);
		}
		else
		{
			OnMovePerformed(moveinput);
		}

		MoveInputObserver = moveinput;
	}*/
}
