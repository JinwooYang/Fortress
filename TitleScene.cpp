#include "DXUT.h"
#include "TitleScene.h"
#include "ScoreBoard.h"
#include "UserDefines.h"
#include "GameScene.h"
#include "ScoreDialog.h"

USING_NS_DX2DX;

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}


void TitleScene::OnInit()
{
	auto bg = Sprite::Create(LR"(Resources/Images/bg.jpg)");
	bg->SetAnchorPoint(Point::ANCHOR_TOP_LEFT);
	this->AddChild(bg);

	auto scoreBoardImg = Sprite::Create(LR"(Resources/Images/score_board.png)");
	scoreBoardImg->SetPosition(WINDOW_X / 2, WINDOW_Y / 2);
	this->AddChild(scoreBoardImg);

	auto scoreBoardText = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 40, L"SCOREBOARD");
	scoreBoardText->SetPosition(WINDOW_X / 2, WINDOW_Y * 0.15f);
	this->AddChild(scoreBoardText);

	auto enterToStart = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 40, L"Press Enter To Start");
	enterToStart->SetPosition(WINDOW_X / 2, WINDOW_Y * 0.8f);
	this->AddChild(enterToStart);

	auto scoreBoardBox = scoreBoardImg->GetBoundingBox();

	auto scoreBoard = ScoreBoard::GetInstance();
	for (int i = 0; i < SCOREBOARD_MAX; ++i)
	{
		auto scoreInfo = scoreBoard->GetScoreInfo(i);
		
		wchar_t rankingStr[256];
		wsprintf(rankingStr, L"%d.", i + 1);
		auto ranking = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 30, rankingStr);
		ranking->SetPosition(scoreBoardBox.left + 300, scoreBoardBox.top + 100 + (i * 30));
		ranking->SetAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		this->AddChild(ranking);

		wchar_t nameStr[256];
		MultiByteToWideChar(CP_ACP, 0, scoreInfo.name.c_str(), -1, nameStr, 256);
		auto name = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 30, nameStr);
		name->SetPosition(scoreBoardBox.left + 400, ranking->GetPositionY());
		this->AddChild(name);

		wchar_t scoreStr[256];
		wsprintf(scoreStr, L"%d", scoreInfo.score);
		auto score = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 30, scoreStr);
		score->SetPosition(scoreBoardBox.left + 500, ranking->GetPositionY());
		this->AddChild(score);

		for (int starIndex = 0; starIndex < STAR_NUM; ++starIndex)
		{
			auto starEmpty = Sprite::Create(LR"(Resources/Images/star_empty.png)");
			starEmpty->SetScale(0.2f);
			starEmpty->SetPosition(scoreBoardBox.left + 600 + (starIndex * 30), ranking->GetPositionY());
			this->AddChild(starEmpty);

			if (scoreInfo.score > 300 + (starIndex * 300))
			{
				auto starFull = Sprite::Create(LR"(Resources/Images/star_full.png)");
				starFull->SetScale(0.2f);
				starFull->SetPosition(scoreBoardBox.left + 600 + (starIndex * 30), ranking->GetPositionY());
				this->AddChild(starFull);
			}
		}
	}
}


void TitleScene::OnUpdate()
{
	if (!_SceneChange && GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		_SceneChange = true;
		Director::GetInstance()->ReplaceScene(GameScene::Create());
	}
}


void TitleScene::OnExit()
{

}


void TitleScene::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
	bool *pbNoFurtherProcessing, void *pUserContext)
{
}