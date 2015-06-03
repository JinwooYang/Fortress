#pragma once
#include "dx2dx.h"
#include "UserDefines.h"

class Bullet
	: public dx2dx::Sprite
{
private:
	DISALLOW_COPY_AND_ASSIGN(Bullet);
	Bullet();
	~Bullet();

	float _PowerX, _PowerY;

public:
	CREATE_FUNC(Bullet);
	void Shoot(float radianAngle, float power);
	void Update();

	bool GroundCollision()
	{
		return (this->GetWorldPositionY() > GROUND_Y);
	}
};

