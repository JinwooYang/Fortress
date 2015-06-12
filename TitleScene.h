#pragma once
#include "dx2dx.h"
#include "Tank.h"

class TitleScene
	: public dx2dx::Scene
{
private:
	DISALLOW_COPY_AND_ASSIGN(TitleScene);
	TitleScene();
	~TitleScene();

	Tank* _Tank;
	dx2dx::Sprite* _Goal;

private:
	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
	virtual void OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
		bool *pbNoFurtherProcessing, void *pUserContext) override;

	int ShowResultMessage(int curScore);

public:
	CREATE_FUNC(TitleScene);
};

