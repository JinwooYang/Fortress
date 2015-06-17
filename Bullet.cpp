#include "DXUT.h"
#include "Bullet.h"
#include "UserDefines.h"

USING_NS_DX2DX;

Bullet::Bullet() :
Sprite(LR"(Resources/Images/bullet.png)"),
_RadianAngle(0.f),
_Power(0.f),
_CurFrame(0.f)
{
}


Bullet::~Bullet()
{
}


void Bullet::Shoot(float radianAngle, float power)
{
	_RadianAngle = radianAngle;
	_Power = power;
	_StartPos = this->GetPosition();
}


void Bullet::Update()
{
	//_PowerY += GRAVITY;
	//this->MoveBy(_PowerX, _PowerY);

	++_CurFrame;

	float powerX = cos(_RadianAngle) * _Power;
	float powerY = sin(_RadianAngle) * _Power;

	float t = _CurFrame;

	float distX = t * powerX;
	float distY = t * powerY + (GRAVITY / 2) * (t * t);

	SetPosition(_StartPos.x + distX,
		_StartPos.y + distY);
}