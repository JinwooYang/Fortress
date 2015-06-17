#pragma once
#include "dx2dx.h"
#include "UserDefines.h"

class TrackPoint
	: public dx2dx::Sprite
{
private:
	TrackPoint();
	~TrackPoint();

	bool _Active;

	dx2dx::Point _StartPos;

	float _Power;
	float _Life;

	float _RadianAngle;

	float _CurFrame;

public:
	CREATE_FUNC(TrackPoint);

	void Update();

	void SetStartPos(dx2dx::Point pos)
	{
		_StartPos = pos;
	}

	bool IsActive()
	{
		return _Active;
	}

	void SetAngle(float radianAngle)
	{
		_RadianAngle = radianAngle;
	}

	void SetPower(float power)
	{
		_Power = power;
	}

	void SetLife(float life)
	{
		_Life = life;
	}

	void SetElapseTime(float sec)
	{
		_CurFrame = sec * FPS;
	}
};

