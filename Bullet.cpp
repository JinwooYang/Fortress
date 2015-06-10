#include "DXUT.h"
#include "Bullet.h"
#include "UserDefines.h"

USING_NS_DX2DX;

Bullet::Bullet() :
Sprite(LR"(Resources/Images/bullet.png)")
{
}


Bullet::~Bullet()
{
}


void Bullet::Shoot(float radianAngle, float power)
{
	_PowerX = cos(radianAngle) * power;
	_PowerY = sin(radianAngle) * power;

}


void Bullet::Update()
{
	_PowerY += GRAVITY;
	this->MoveBy(_PowerX, _PowerY);
}