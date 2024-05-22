#include "SphereCollider.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include <iostream>



float clamp(float value, float min, float max);

bool SphereCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
	// Get the difference between objects
	LLGP::Vector2 diff = other.GetPosition() - GetPosition();
	// Get the Radii sum of the two objects 
	float radiiSum = other.GetRadius() + GetRadius();
	// Check to see if we are colliding
	if (diff.GetMagnitude() < radiiSum)
	{
		// Set the collision normal
		out.collisionNormal = diff;

		// Normalise the collision normal
		out.collisionNormal.Normalise();
		
		// Populate the contact point list to 1 in the collision manifold
		out.contactPointCount = 1;

		// Set the position in the collision manifold 
		out.points[0].Position = GetPosition() + (out.collisionNormal * GetRadius());

		// Set the penetration depth in the collision manifold
		out.points[0].penDepth = fabs(diff.GetMagnitude() - radiiSum);

		return true;
	}
	return false;

	
}

bool SphereCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{
	

	LLGP::Vector2f center = this->GetPosition();

	LLGP::Vector2f AABBHalfExtents = other.GetHalfExtents() / 2;
	LLGP::Vector2f AABBcenter = other.GetPosition();

	LLGP::Vector2f diff = center - AABBcenter;
	float  clampX = clamp(diff.x, -AABBHalfExtents.x, AABBHalfExtents.x);
	float clampY = clamp(diff.y, -AABBHalfExtents.y, AABBHalfExtents.y);

	LLGP::Vector2f clamp(clampX, clampY);

	LLGP::Vector2f closest = AABBcenter + clamp;

	diff = closest - center;

	if (diff.GetMagnitude() < this->_radius) {
		out.collisionNormal = diff;
		out.collisionNormal.Normalise();
		out.contactPointCount = 1.0f;
		out.points[0].Position = GetPosition() + (out.collisionNormal * this->_radius);
		out.points->penDepth = fabs(diff.GetMagnitude() - this->_radius);
		return true;
	}
	return false;

	

}

bool SphereCollider::CollidesWith(LineCollider& other, CollisionManifold& out)
{

	return other.LineCircle(other.GetHeadPoint().x,other.GetHeadPoint().y,other.GetTailPoint().x,other.GetTailPoint().y,GetPosition().x,GetPosition().y,this->_radius);
}



float  clamp(float value, float min, float max)
{
	return std::max(min, std::min(max, value));
}
