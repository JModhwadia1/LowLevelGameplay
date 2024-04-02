#pragma once
#include "Vector2.h"
#include "Transform.h"

class SphereCollider;
class BoxCollider;

struct ContactPoint {
	LLGP::Vector2f Position;
	float penDepth;
};
struct CollisionManifold
{
	int contactPointCount;
	ContactPoint points[4];
	LLGP::Vector2f collisionNormal;
	
};
class Collider abstract
{
protected:
	Transform* _transform;

public:
	Collider(Transform* transform) { _transform = transform; }

	virtual bool CollidesWith(Collider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(BoxCollider& other, CollisionManifold& out) = 0;

	LLGP::Vector2f GetPosition() const { return _transform->GetPosition(); }
};

