#include "DXUT.h"
#include "ScaleTo.h"
#include "Node.h"

USING_NS_DX2DX;

ScaleTo::ScaleTo(float duration, Point scale) :
_Duration(duration),
_TargetScale(scale)
{
}


ScaleTo::~ScaleTo()
{
}


ScaleTo* ScaleTo::Create(float duration, Point scale)
{
	auto scaleTo = new ScaleTo(duration, scale);
	scaleTo->AutoRelease();

	return scaleTo;
}


void ScaleTo::OnStartWithTarget(Node* const node)
{
	_OrgScale = node->GetScale();

	_ScaleDelta = Point((_TargetScale.x - _OrgScale.x) / (_Duration * 60.f),
						(_TargetScale.y - _OrgScale.y) / (_Duration * 60.f));

}


void ScaleTo::Run(Node* const node)
{
	Point nodeScale = node->GetScale();
	nodeScale += _ScaleDelta;
	node->SetScale(nodeScale);

	if (_OrgScale.x < _TargetScale.x && nodeScale.x > _TargetScale.x ||
		_OrgScale.x > _TargetScale.x && nodeScale.x < _TargetScale.x)
	{
		nodeScale.x = _TargetScale.x;
	}
	if (_OrgScale.y < _TargetScale.y && nodeScale.y > _TargetScale.y ||
		_OrgScale.y > _TargetScale.y && nodeScale.y < _TargetScale.y)
	{
		nodeScale.y = _TargetScale.y;
	}

	if (nodeScale == _TargetScale)
	{
		ActionFinish();
	}
}


Action* ScaleTo::Clone() const
{
	auto clone = ScaleTo::Create(this->_Duration, this->_TargetScale);

	return clone;
}


Action* ScaleTo::Reverse() const
{
	auto reverse = ScaleTo::Create(this->_Duration, this->_OrgScale);

	return reverse;
}