#pragma once
#include "dx2dx.h"

class ScoreDialog
	: public dx2dx::Node
{
private:
	DISALLOW_COPY_AND_ASSIGN(ScoreDialog);
	ScoreDialog();
	~ScoreDialog();

	dx2dx::Sprite*  _DialogImg;
	dx2dx::Button* _BtnYes, *_BtnNo;

	std::function<void()> _CloseCallBack = []{};

public:

	void SetCloseCallBack(std::function<void()> callback);

	static ScoreDialog* Create()
	{
		auto* dialog = new ScoreDialog();
	}
};

