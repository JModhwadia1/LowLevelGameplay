#include "SphereCollider.h"

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
	return false;
}
