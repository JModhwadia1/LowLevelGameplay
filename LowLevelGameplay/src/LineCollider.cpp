#include "LineCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

bool LineCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
	mHeadPoint.x = GetPosition().x + m_sprite.getScale().x;
	mHeadPoint.y = GetPosition().y + m_sprite.getScale().y;

	mTailPoint.x = GetPosition().x - m_sprite.getScale().x;
	mTailPoint.y = GetPosition().y - m_sprite.getScale().y;

	return LineCircle(mHeadPoint.x, mHeadPoint.y, mTailPoint.x, mTailPoint.y, other.GetPosition().x, other.GetPosition().y, other.GetRadius());
}

bool LineCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{
	LLGP::Vector2f otherMin = other.GetMin();
	LLGP::Vector2f otherMax = other.GetMax();

	mHeadPoint.x = GetPosition().x + m_sprite.getScale().x;
	mHeadPoint.y = GetPosition().y + m_sprite.getScale().y;

	mTailPoint.x = GetPosition().x - m_sprite.getScale().x;
	mTailPoint.y = GetPosition().y - m_sprite.getScale().y;

	if (this->mHeadPoint.x < otherMin.x ||
		this->mHeadPoint.y < otherMin.y ||
		this->mTailPoint.x > otherMax.x ||
		this->mTailPoint.y > otherMax.y)
		return false;

	return true;
}

bool LineCollider::CollidesWith(LineCollider& other, CollisionManifold& out)
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

LLGP::Vector2f LineCollider::GetHeadPoint()
{
	mHeadPoint.x = GetPosition().x + m_sprite.getScale().x;
	mHeadPoint.y = GetPosition().y + m_sprite.getScale().y;

	return mHeadPoint;
}

LLGP::Vector2f LineCollider::GetTailPoint()
{


	mTailPoint.x = GetPosition().x - m_sprite.getScale().x;
	mTailPoint.y = GetPosition().y - m_sprite.getScale().y;

	return mTailPoint;
}
bool LineCollider::LineCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r)
{
	// is either end INSIDE the circle?
 // if so, return true immediately
	bool inside1 = PointCircle(x1, y1, cx, cy, r);
	bool inside2 = PointCircle(x2, y2, cx, cy, r);
	if (inside1 || inside2) return true;

	// get length of the line
	float distX = x1 - x2;
	float distY = y1 - y2;
	float len = sqrt((distX * distX) + (distY * distY));

	// get dot product of the line and circle
	float dot = (((cx - x1) * (x2 - x1)) + ((cy - y1) * (y2 - y1))) / pow(len, 2);

	// find the closest point on the line
	float closestX = x1 + (dot * (x2 - x1));
	float closestY = y1 + (dot * (y2 - y1));

	// is this point actually on the line segment?
	// if so keep going, but if not, return false
	bool onSegment = LinePoint(x1, y1, x2, y2, closestX, closestY);
	if (!onSegment) return false;


	// get distance to closest point
	distX = closestX - cx;
	distY = closestY - cy;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= r) {
		return true;
	}
	return false;
}
bool LineCollider::PointCircle(float px, float py, float cx, float cy, float r)
{
	// get distance between the point and circles center 
	// using the Pythagoreaan theorem
	float distX = px - cx;
	float distY = py - cy;

	float distance = sqrt((distX * distX) + (distY * distY));
	
	// if the distance is less than the circles
	// radius the point is inside 
	if (distance <= r) {
		return true;
	}
	return false;
}
