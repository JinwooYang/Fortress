#pragma once
#include "dx2dx.h"

const int STAR_NUM = 3;

class ScoreDialog
	: public dx2dx::Node
{
private:
	DISALLOW_COPY_AND_ASSIGN(ScoreDialog);
	ScoreDialog(int score, std::function<void()> callback = []{});
	~ScoreDialog();

	int _Score;

	dx2dx::Sprite* _BackImg;
	dx2dx::Sprite* _StarEmpty[STAR_NUM];
	dx2dx::Sprite* _StarFull[STAR_NUM];
	dx2dx::Sprite* _EditControl;

	dx2dx::Label* _ScoreText, *_InputYourNameText, *_NameText;

	std::function<void()> _CloseCallBack = []{};

	wchar_t _Name[5];

	void InitBackImg();
	void InitStarImg();
	void InitText();

	float ActionBackImg(float waitTime);
	float ActionStarImg(float waitTime);
	float ActionText(float waitTime);

	void OKBtnCallBack();

public:
	static ScoreDialog* Create(int score, std::function<void()> callback)
	{
		auto* dialog = new ScoreDialog(score, callback);
		dialog->AutoRelease();

		return dialog;
	}

	void MsgProc(HWND, UINT, WPARAM, LPARAM);
};

