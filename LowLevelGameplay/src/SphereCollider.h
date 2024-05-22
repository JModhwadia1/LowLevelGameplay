#pragma once
#include "Collider.h"
class SphereCollider :  public Collider
{
public:
	SphereCollider(Transform* transform, float radius) : Collider(transform) { _radius = radius; }
	
	 bool CollidesWith(Collider& other, CollisionManifold& out) override { return other.CollidesWith(*this, out); }
	 bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
	 bool CollidesWith(BoxCollider& other, CollisionManifold& out) override;
	 bool CollidesWith(LineCollider& other, CollisionManifold& out) override;
	float GetRadius() { return _radius; }


private:
	float _radius = 1.0f;
};

