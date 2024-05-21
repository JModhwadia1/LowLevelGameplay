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

	if (diff.GetMagnitude() < other.GetRadius()) {
		out.collisionNormal = diff;
		out.collisionNormal.Normalise();
		out.contactPointCount = 1;
		out.points[0].Position = GetPosition() + (out.collisionNormal * other.GetRadius());
		out.points[0].penDepth = fabs(diff.GetMagnitude() - other.GetRadius());
		return true;
	}
	return false;
	
}

bool BoxCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{
	// Get the center of the collider
	_center = this->GetPosition();
	// Get the max of this collider
	_max = _center + (_halfExtents / 2);
	// Get the min of this collider
	_min = _center - (_halfExtents / 2);

	// Get the Min, Max and Center of the other collider
	LLGP::Vector2f theirMax, theirMin, theirCenter;
	theirCenter = other.GetPosition();
	theirMax = theirCenter + (other.GetHalfExtents() / 2);
	theirMin = theirCenter - (other.GetHalfExtents() / 2);

	// Check collision
	if (this->_max.x < theirMin.x || this->_min.x > theirMax.x)
		return false;
	if (this->_max.y < theirMin.y || this->_min.y > theirMax.y)
		return false;
	
	
	out.contactPointCount = 1;
	out.collisionNormal = other.GetPosition() - GetPosition();
	out.collisionNormal.Normalise();
	out.points[0].Position = this->GetPosition() + out.collisionNormal;
	out.points[0].penDepth = DistanceToPointAABB(out.points[0].Position, *this);

	return true;
	
	
}
bool BoxCollider::CollidesWith(LineCollider& other, CollisionManifold& out)
{
	LLGP::Vector2f otherHeadPoint = other.GetHeadPoint();
	LLGP::Vector2f otherTailPoint = other.GetTailPoint();

	if (this->_max.x < otherTailPoint.x ||
		this->_max.y < otherTailPoint.y ||
		this->_min.x > otherHeadPoint.x ||
		this->_min.y > otherHeadPoint.y)
		return false;
	return true;
}
float  clamp2(float value, float min, float max)
{
	return std::max(min, std::min(max, value));
}
