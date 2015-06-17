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

	float _RadianAngle;
	float _Power;

	dx2dx::Point _StartPos;

	float _CurFrame;

public:
	CREATE_FUNC(Bullet);
	void Shoot(float radianAngle, float power);
	void Update();

	bool GroundCollision()
	{
		return (this->GetWorldPositionY() > GROUND_Y);
	}
};

