#include "DXUT.h"
#include "UserDefines.h"
#include "GameScene.h"
#include <fstream>
#include "ScoreBoard.h"
#include "ScoreDialog.h"

USING_NS_DX2DX;

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
	LOG("Delete : Title Scene\n");
}


void GameScene::OnInit()
{
	auto bg = Sprite::Create(LR"(Resources/Images/bg.jpg)");
	bg->SetAnchorPoint(Point::ANCHOR_TOP_LEFT);
	this->AddChild(bg);

	_Tank = Tank::Create();
	_Tank->SetPosition(WINDOW_X * 0.2f, GROUND_Y);

	_Goal = Sprite::Create(LR"(Resources/Images/goal.png)");
	_Goal->SetPosition(WINDOW_X * 0.9f, GROUND_Y);
	_Goal->SetAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);

	this->AddChild(_Tank);
	this->AddChild(_Goal);
}

void GameScene::OnUpdate()
{
	_Tank->Update();

	if (_Tank->BulletAndGroundCollision())
	{
		//auto scoreBoard = ScoreBoard::GetInstance();

		int curScore = SCORE_MAX - abs(_Goal->GetWorldPositionX() - _Tank->GetBullet()->GetWorldPositionX());

		/*if (curScore > scoreBoard->GetLowestScore())
		{
			scoreBoard->SubmitScore(curScore);
		}*/

		ShowScoreDialog(curScore);
	}
}

void GameScene::OnExit()
{
}

void GameScene::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
	bool *pbNoFurtherProcessing, void *pUserContext)
{
	if (_ScoreDialogIsOpen)
	{
		_ScoreDialog->MsgProc(hWnd, uMsg, wParam, lParam);
	}
}


void GameScene::ShowScoreDialog(int curScore)
{
	this->Pause();
	_ScoreDialogIsOpen = true;

	_ScoreDialog = ScoreDialog::Create(curScore, [=]
	{
		this->Resume();
		_ScoreDialogIsOpen = false;
	});
	_ScoreDialog->SetPosition(WINDOW_X / 2, WINDOW_Y / 2);

	this->AddChild(_ScoreDialog);
}