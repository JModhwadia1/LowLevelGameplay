#pragma once
#include "Collider.h"
class LineCollider : public Collider
{
public:
	LineCollider(Transform* transform, LLGP::Vector2f start, LLGP::Vector2f end) : Collider(transform) { mStartPoint = start; mEndPoint = end; }

	bool CollidesWith(Collider& other, CollisionManifold& out) override { return other.CollidesWith(*this, out); }
	bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
	bool CollidesWith(BoxCollider& other, CollisionManifold& out) override;

	bool LinePoint(float x1, float y1, float x2, float y2, float px, float py);
private:
	LLGP::Vector2f mStartPoint;
	LLGP::Vector2f mEndPoint;
};

