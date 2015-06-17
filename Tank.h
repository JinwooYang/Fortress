#pragma once
#include "dx2dx.h"
#include "Bullet.h"
#include <array>
#include "TrackPoint.h"

const int TRACK_MAX = 8;

class Tank
	: public dx2dx::Node
{
private:
	DISALLOW_COPY_AND_ASSIGN(Tank);
	Tank();
	~Tank();

	dx2dx::Sprite* _Body, *_Head;
	dx2dx::Sprite* _Gauge_Back, *_Gauge_Front;
	Bullet* _Bullet;

	//ÃÑ¾Ë ±Ëµµ
	std::vector<TrackPoint*> _Track;
	int _TrackUpdateFrame = 0;

	bool _Shooting = false;
	bool _SpaceKeyUp = true;

	const float _MaxPower = 25.f;
	float _PowerChargeVal = 0.1f;
	float _DegreeAngle = -25.f, _Power = 0.f;

private:
	void ControlAngle();
	void ControlPower();
	void Shoot();
	dx2dx::Point CalcBulletPos();
	void TrackAnimation();
	void PowerCharge();

public:
	CREATE_FUNC(Tank);
	void Update();
	Bullet* GetBullet() const
	{
		return _Bullet;
	}

	float GetPower() const
	{
		return _Power;
	}

	bool BulletAndGroundCollision()
	{
		return _Bullet->GroundCollision();
	}
};

