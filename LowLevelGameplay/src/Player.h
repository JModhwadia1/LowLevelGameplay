#pragma once
#include "Vector2.h"
#include <SFML/Graphics.hpp>
//#include "Transform.h"
//#include "Rigidbody.h"
#include "GameObject.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

enum AnimationIndex
{
	WalkingUp,
	WalkingDown,
	WalkingLeft,
	WalkingRight,
	Count
};


class Player : public GameObject
{
public:
	explicit Player(GameWorld* world, sf::Texture* texture);

	void Update(float dt);
	void Render(sf::RenderWindow* window);

	LLGP::Vector2f direction;
	void UpdateMovement(float dt);
	float AccelerationSpeed = 200.0f;
	float mMaxSpeed = 300.0f;
private:
	Animation animations[int(AnimationIndex::Count)]; // 4 anims
	AnimationIndex currentAnimation = AnimationIndex::WalkingLeft;
	BoxCollider* _boxCollider;
	SphereCollider* _sphereCollider;

};

