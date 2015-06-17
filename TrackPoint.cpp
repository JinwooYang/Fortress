#include "DXUT.h"
#include "TrackPoint.h"
#include "UserDefines.h"

USING_NS_DX2DX;

TrackPoint::TrackPoint() :
Sprite(L"Resources/Images/track_point.png"),
_Active(true),
_Power(0.f),
_Life(0.f),
_CurFrame(0)
{
}


TrackPoint::~TrackPoint()
{
}


void TrackPoint::Update()
{
	if (!_Active) return;

	++_CurFrame;

	float powerX = cos(_RadianAngle) * _Power;
	float powerY = sin(_RadianAngle) * _Power;

	//점이 너무 빨리 이동해서 딜레이를 주는 용도
	float delay = 4.f;

	float t = _CurFrame / delay;

	float distX = t * powerX;
	float distY = t * powerY + (GRAVITY / 2) * (t * t);

	SetPosition(_StartPos.x + distX,
				_StartPos.y + distY);

	SetScale(1.f - (_CurFrame / (_Life * FPS)));

	if (_CurFrame > _Life * FPS)
	{
		_Active = false;
	}
}