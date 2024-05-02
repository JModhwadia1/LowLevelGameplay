#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Collider.cpp"
#include "LineCollider.h"
float  clamp2(float value, float min, float max);


bool BoxCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
	LLGP::Vector2f center = other.GetPosition();

	LLGP::Vector2f AABBHalfExtents = this->GetHalfExtents() / 2;
	LLGP::Vector2f AABBcenter = this->GetPosition();

	LLGP::Vector2f diff = center - AABBcenter;
	float  clampX = clamp2(diff.x, -AABBHalfExtents.x, AABBHalfExtents.x);
	float clampY = clamp2(diff.y, -AABBHalfExtents.y, AABBHalfExtents.y);

	LLGP::Vector2f clamp(clampX, clampY);

	LLGP::Vector2f closest = AABBcenter + clamp;

	diff = closest - center;

	return diff.GetMagnitude() < other.GetRadius();
}

bool BoxCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{
	// Get the center of the collider
	_center = this->GetPosition();;
	// Get the max of this collider
	_max = _center + (_halfExtents / 2);
	// Get the min of this collider
	_min = _center - (_halfExtents / 2);

	// Get the Min, Max and Center of the other collider
	LLGP::Vector2f theirMax, theirMin, theirCenter;
	theirCenter = other.GetPosition();
	theirMax = theirCenter + (other.GetHalfExtents() / 2);
	theirMin = theirCenter - (other.GetHalfExtents() / 2);

	// Check to see if there is collision 
	if (this->_max.x < theirMin.x || 
		this->_max.y < theirMin.y || 
		this->_min.x > theirMax.x || 
		this->_min.y > theirMax.y)
		return false;
	/*if (this->_max.y < theirMin.y || this->_min.y > theirMax.y);
		return false;*/
		
	out.contactPointCount = 1;
	out.collisionNormal = other.GetPosition() - GetPosition();
	out.collisionNormal.Normalise();
	out.points[0].Position = GetPosition() + out.collisionNormal;
	out.points[0].penDepth = DistanceToPointAABB(out.points[0].Position, *this);

	return true;
	//bool CollisionX = this->GetPosition().x + 25.0f >= other.GetPosition().x && other.GetPosition().x + 25.0f >= this->GetPosition().x;
	//bool CollisionY = this->GetPosition().y + 55.0f >= other.GetPosition().y && other.GetPosition().y + 55.0f >= this->GetPosition().y;

	//return CollisionX && CollisionY;
	//
	//	 
	
}
bool BoxCollider::CollidesWith(LineCollider& other, CollisionManifold& out)
{
	LLGP::Vector2f otherHeadPoint = other.GetHeadPoint();
	LLGP::Vector2f otherTailPoint = other.GetTailPoint();

	if (this->_max.x < otherTailPoint.x ||
		this->_max.y < otherTailPoint.y ||
		this->_max.x > otherHeadPoint.x ||
		this->_max.y > otherHeadPoint.y)
		return false;
	return true;
}
float  clamp2(float value, float min, float max)
{
	return std::max(min, std::min(max, value));
}
