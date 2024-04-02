#include "BoxCollider.h"
#include "Collider.cpp"

bool BoxCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
	return false;
}

bool BoxCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{
	// Get the center of the collider
	_center = this->GetPosition();
	// Get the max of this collider
	_max = _center + _halfExtents;
	// Get the min of this collider
	_min = _center - _halfExtents;

	// Get the Min, Max and Center of the other collider
	LLGP::Vector2f theirMax, theirMin, theirCenter;
	theirCenter = other.GetPosition();
	theirMax = theirCenter + other.GetHalfExtents();
	theirMin = theirCenter - _halfExtents;

	// Check to see if there is collision 
	if (this->_max.x < theirMin.x || this->_min.x > theirMax.x)
		return false;
	if (this->_max.y < theirMin.y || this->_min.y > theirMax.y);
		return false;
		
	out.contactPointCount = 1;
	out.collisionNormal = other.GetPosition() - GetPosition();
	out.collisionNormal.Normalise();
	out.points[0].Position = GetPosition() + out.collisionNormal;
	out.points[0].penDepth = DistanceToPointAABB(out.points[0].Position, *this);

	return true;
	
	
}
