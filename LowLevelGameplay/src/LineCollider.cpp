#include "LineCollider.h"

bool LineCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
	
}

bool LineCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{
	return false;
}

bool LineCollider::LinePoint(float x1, float y1, float x2, float y2, float px, float py)
{
	/*LLGP::Vector2f startLine;
	startLine.x = x1;
	startLine.y = x2;

	LLGP::Vector2f endLine;
	endLine.x = x2;
	endLine.y = y2;*/

	// get distance from the point to the two ends of the line
	float d1 = ((px - x1) + (py - y1));
	float d2 = ((px - x2) + (py - y2));

	// get the length of the line
	float lineLength = ((x1 + x2) + (y1 + y2));

	// higher the buffer, the less accurate the collision 
	float buffer = 0.1f;

	if (d1 + d2 >= lineLength - buffer && d1 + d2 <= lineLength + buffer) {
		return true;
	}
	return false;
}
