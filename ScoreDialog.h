#pragma once
#include "dx2dx.h"

class ScoreDialog
	: public dx2dx::Node
{
private:
	DISALLOW_COPY_AND_ASSIGN(ScoreDialog);
	ScoreDialog(int score, std::function<void()> callback = []{});
	~ScoreDialog();

	int _Score;

	dx2dx::Sprite*  _DialogImg, *_EditControl;
	dx2dx::Label* _ScoreText, *_NameText;
	dx2dx::Button* _BtnOK;

	std::function<void()> _CloseCallBack = []{};

	wchar_t _Name[5];

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

