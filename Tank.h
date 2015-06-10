#pragma once
#include "dx2dx.h"
#include "Bullet.h"
#include <array>

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
	//ÃÑ¾Ë ±Ëµµ
	dx2dx::Sprite* _Track[TRACK_MAX];
	Bullet* _Bullet;

	bool _Shooting = false;

	const float _MaxPower = 25.f;
	float _DegreeAngle = -25.f, _Power = 0.f;

	dx2dx::Point CalcBulletPos();
	void CalcTrack();

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

