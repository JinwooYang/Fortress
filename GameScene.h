#pragma once
#include "dx2dx.h"
#include "Tank.h"
#include "ScoreDialog.h"

class GameScene
	: public dx2dx::Scene
{
private:
	DISALLOW_COPY_AND_ASSIGN(GameScene);
	GameScene();
	~GameScene();

	Tank* _Tank;
	dx2dx::Sprite* _Goal;

	ScoreDialog* _ScoreDialog;
	bool _ScoreDialogIsOpen = false;

private:
	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
	virtual void OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
		bool *pbNoFurtherProcessing, void *pUserContext) override;

	void ShowScoreDialog(int curScore);
public:
	CREATE_FUNC(GameScene);
};

