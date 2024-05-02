#pragma once
#include "Collider.h"
class LineCollider : public Collider
{
public:
	LineCollider(Transform* transform, LLGP::Vector2f start, LLGP::Vector2f end,sf::Sprite& sprite) : Collider(transform) { mHeadPoint = start; mTailPoint = end; }

	bool CollidesWith(Collider& other, CollisionManifold& out) override { return other.CollidesWith(*this, out); }
	bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
	bool CollidesWith(BoxCollider& other, CollisionManifold& out) override;
	bool CollidesWith(LineCollider& other, CollisionManifold& out) override;

	bool LinePoint(float x1, float y1, float x2, float y2, float px, float py);
	
	void SetHeadPoint(LLGP::Vector2f HeadPoint) { mHeadPoint = HeadPoint; };
	void SetTailPoint(LLGP::Vector2f TailPoint) { mTailPoint = TailPoint; }
	bool PointCircle(float px, float py, float cx, float cy, float r);
	bool LineCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r);
	LLGP::Vector2f GetHeadPoint();
	LLGP::Vector2f GetTailPoint();
private:
	LLGP::Vector2f mHeadPoint;
	LLGP::Vector2f mTailPoint;
	sf::Sprite m_sprite;
};

