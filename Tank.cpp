#include "DXUT.h"
#include "Tank.h"

USING_NS_DX2DX;

const float TRACKPOINT_LIFE = 5.f;
const float TRACKPOINT_CREATE_CYCLE = 0.5f;

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

	for (float elapseTime = 0.f; elapseTime < TRACKPOINT_LIFE; elapseTime += TRACKPOINT_CREATE_CYCLE)
	{
		auto trackPoint = TrackPoint::Create();
		trackPoint->SetPosition(_Bullet->GetPosition());
		trackPoint->SetElapseTime(elapseTime);
		trackPoint->SetVisible(false);
		this->AddChild(trackPoint);

		_Track.push_back(trackPoint);
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


void Tank::ControlAngle()
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
	_Head->SetRotAngle(_DegreeAngle);
}


void Tank::ControlPower()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		PowerCharge();
		TrackAnimation();
		for (auto trackPoint : _Track)
		{
			trackPoint->SetVisible(true);
		}
	}
}


void Tank::Shoot()
{
	_Shooting = true;
	_Bullet->Shoot(D3DXToRadian(_DegreeAngle), _Power);
	for (auto trackPoint : _Track)
	{
		trackPoint->SetVisible(false);
	}
}


Point Tank::CalcBulletPos()
{
	const int dist = 100;
	return _Head->GetPosition() + Point(cos(D3DXToRadian(_DegreeAngle)) * dist, sin(D3DXToRadian(_DegreeAngle)) * dist);
}


void Tank::TrackAnimation()
{
	++_TrackUpdateFrame;

	if (_TrackUpdateFrame == FPS * TRACKPOINT_CREATE_CYCLE)
	{
   		auto trackPoint = TrackPoint::Create();
		trackPoint->SetPosition(_Bullet->GetPosition());
		trackPoint->SetVisible(false);
		this->AddChild(trackPoint);
		
		_Track.push_back(trackPoint);

		_TrackUpdateFrame = 0;
	}

	for (auto iter = _Track.begin(); iter != _Track.end();)
	{
		auto trackPoint = *iter;

		trackPoint->SetStartPos(_Bullet->GetPosition());
		trackPoint->SetLife(TRACKPOINT_LIFE);
		trackPoint->SetPower(_Power);
		trackPoint->SetAngle(D3DXToRadian(_DegreeAngle));
		trackPoint->Update();

		if (!trackPoint->IsActive())
		{
			trackPoint->Release();
			iter = _Track.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}


void Tank::PowerCharge()
{
	_Power += _PowerChargeVal;

	if (_Power >= _MaxPower)
	{
		_Power = _MaxPower;
		_PowerChargeVal = -_PowerChargeVal;
	}
	else if (_Power <= 0.f)
	{
		_Power = 0.f;
		_PowerChargeVal = -_PowerChargeVal;
	}
}


void Tank::Update()
{
	if (!_Shooting)
	{
		ControlAngle();

		_Bullet->SetPosition(CalcBulletPos());

		ControlPower();

		if (KEY_UP_ONCE(VK_SPACE, &_SpaceKeyUp))
		{
			Shoot();
		}
		_Gauge_Front->SetScaleY(_Power / _MaxPower);

	}
	else
	{
		_Bullet->Update();
	}
}
