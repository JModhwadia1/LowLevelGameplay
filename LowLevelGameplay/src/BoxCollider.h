#pragma once
#include "Collider.h"
class BoxCollider : public Collider
{
public:

	BoxCollider(Transform* transform, LLGP::Vector2f halfextents) : Collider(transform) { _halfExtents = halfextents; }

	bool CollidesWith(Collider& other, CollisionManifold& out) override { return other.CollidesWith(*this, out);}
	bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
	bool CollidesWith(BoxCollider& other, CollisionManifold& out) override;
	
	LLGP::Vector2f GetCenter() { return _center; }
	void SetCenter(LLGP::Vector2f center) { _center = center; }

	LLGP::Vector2f GetMin() { return _min; }
	LLGP::Vector2f GetMax() { return _max; }

	LLGP::Vector2f GetHalfExtents() { return _halfExtents; }


private:
	LLGP::Vector2f _center;
	LLGP::Vector2f _halfExtents;
	LLGP::Vector2f _max;
	LLGP::Vector2f _min;

};

