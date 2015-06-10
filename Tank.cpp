#include "DXUT.h"
#include "Tank.h"

USING_NS_DX2DX;

Tank::Tank() :
_Body(Sprite::Create(LR"(Resources/Images/tank_body.png)")),
_Head(Sprite::Create(LR"(Resources/Images/tank_head.png)")),
_Gauge_Back(Sprite::Create(LR"(Resources/Images/gauge_back.png)")),
_Gauge_Front(Sprite::Create(LR"(Resources/Images/gauge_front.png)")),
_Bullet(Bullet::Create())
{
	_Body->SetAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	auto bodyBox = _Body->GetBoundingBox();

	_Head->SetPosition(bodyBox.GetMidX(), bodyBox.GetMinY());
	_Head->SetAnchorPoint(Point(0.2f, 0.5f));

	_Gauge_Back->SetPosition(-150.f, -50.f);
	_Gauge_Back->SetAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);

	_Gauge_Front->SetPosition(_Gauge_Back->GetPosition());
	_Gauge_Front->SetAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);


	_Bullet->SetPosition(CalcBulletPos());

	for (int i = 0; i < TRACK_MAX; ++i)
	{
		_Track[i] = Sprite::Create(LR"(Resources/Images/track_point.png)");
		_Track[i]->SetPosition(_Bullet->GetPosition());
		this->AddChild(_Track[i]);
	}


	this->AddChild(_Bullet);
	this->AddChild(_Gauge_Back);
	this->AddChild(_Gauge_Front);
	this->AddChild(_Head);
	this->AddChild(_Body);
}


Tank::~Tank()
{
}


Point Tank::CalcBulletPos()
{
	return _Head->GetPosition() + Point(cos(D3DXToRadian(_DegreeAngle)) * 100, sin(D3DXToRadian(_DegreeAngle)) * 100);
}


void Tank::CalcTrack()
{
	//몇 프레임 후의 궤적에 점을 그릴것인지 저장하는 변수
	const int frame = 10;

	for (int i = 0; i < TRACK_MAX; ++i)
	{
		Point pos = _Bullet->GetPosition();
		Point dist = Point(cos(D3DXToRadian(_DegreeAngle)) * _Power, sin(D3DXToRadian(_DegreeAngle)) * _Power);

		for (int j = 0; j < frame * i; ++j)
		{
			dist.y += GRAVITY;
			pos += dist;
		}
		_Track[i]->SetPosition(pos);
	}
}


void Tank::Update()
{
	if (!_Shooting)
	{

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			++_DegreeAngle;
			if (_DegreeAngle > -25.f)
			{
				_DegreeAngle = -25.f;
			}
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			--_DegreeAngle;
			if (_DegreeAngle < -180.f + 25.f)
			{
				_DegreeAngle = -180.f + 25.f;
			}
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			_Power -= 0.1f;
			if (_Power < 0.f)
			{
				_Power = 0.f;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			_Power += 0.1f;
			if (_Power > _MaxPower)
			{
				_Power = _MaxPower;
			}
		}

		_Head->SetRotAngle(_DegreeAngle);
		_Bullet->SetPosition(CalcBulletPos());
		CalcTrack();

		_Gauge_Front->SetScaleY(_Power / _MaxPower);

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			_Shooting = true;
			_Bullet->Shoot(D3DXToRadian(_DegreeAngle), _Power);
		}

	}
	else
	{
		_Bullet->Update();
	}
}
