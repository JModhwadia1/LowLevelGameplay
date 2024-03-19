#include "Rigidbody.h"

Rigidbody::Rigidbody(Transform* transform)
{
	_transform = transform;
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update(float deltaTime)
{
	LLGP::Vector2f pos = _transform->GetPosition();
	//mVelocity += mAcceleration * deltaTime;

	mVelocity = mDirection * mMaxSpeed;
	//Clamp Speed
   /*if (LLGP::LengthSq(mVelocity) > (mMaxSpeed * mMaxSpeed))
   {
	   mVelocity.Normalised();
	   mVelocity *= mMaxSpeed;
   }*/

   /*if (((mVelocity.x * mVelocity.x) + (mVelocity.y * mVelocity.y)) > (mMaxSpeed * mMaxSpeed))
   {
	   mVelocity = mVelocity.Normalised();
	   mVelocity *= mMaxSpeed;
   }*/

   //std::cout << direction.x << direction.y << std::endl;
   //std::cout << "x " << mVelocity.x <<"y " << mVelocity.y << std::endl;
	pos += mVelocity * deltaTime;
	_transform->SetPosition(pos);
}

void Rigidbody::AddForce(LLGP::Vector2f Force)
{
	mVelocity += Force;
}
