#include "DXUT.h"
#include "UserDefines.h"
#include "TitleScene.h"
#include <fstream>
#include "ScoreBoard.h"

USING_NS_DX2DX;

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
	LOG("Delete : Title Scene\n");
}


void TitleScene::OnInit()
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

void TitleScene::OnUpdate()
{
	_Tank->Update();

	if (_Tank->BulletAndGroundCollision())
	{
		auto scoreBoard = ScoreBoard::GetInstance();

		int curScore = SCORE_MAX - abs(_Goal->GetWorldPositionX() - _Tank->GetBullet()->GetWorldPositionX());

		if (curScore > scoreBoard->GetLowestScore())
		{
			scoreBoard->SubmitScore(curScore);
		}

		//int highScore = GetHighScore();

		//if (curScore > highScore)
		//{
		//	SetHighScore(curScore);
		//	highScore = curScore;
		//}

		int msgID = ShowResultMessage(curScore);
		if (msgID == IDRETRY)
		{
			Director::GetInstance()->ReplaceScene(TitleScene::Create());
		}
		else if (msgID == IDCANCEL)
		{
			GAME_SHUTDOWN();
		}
	}
}

void TitleScene::OnExit()
{
}

void TitleScene::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
	bool *pbNoFurtherProcessing, void *pUserContext)
{
}


int TitleScene::ShowResultMessage(int curScore)
{
	wchar_t str[256];
	wsprintf(str, L"현재점수 : %d\n 재시작 하시겠습니까?", curScore);

	int msgID = MessageBox(DXUTGetHWND(), str, L"결과", MB_RETRYCANCEL);
	
	return msgID;
}