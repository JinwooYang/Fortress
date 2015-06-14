#include "DXUT.h"
#include "TitleScene.h"
#include "ScoreBoard.h"
#include "UserDefines.h"
#include "GameScene.h"

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

	auto TopName = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 40, L"NAME");
	TopName->SetColorA(0);
	TopName->SetPosition(WINDOW_X * 0.4, WINDOW_Y * 0.1);
	this->AddChild(TopName);

	auto TopScore = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 40, L"SCORE");
	TopScore->SetColorA(0);
	TopScore->SetPosition(WINDOW_X * 0.6, WINDOW_Y * 0.1);
	this->AddChild(TopScore);

	auto PressEnter = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 40, L"엔터를 눌러 시작하세요.");
	PressEnter->SetColorA(0);
	PressEnter->SetPosition(WINDOW_X / 2, WINDOW_Y / 2);
	this->AddChild(PressEnter);

	auto fadeInAction = RepeatForever::Create
	(
		Sequence::Create
		({
			TintTo::Create(1.f, Color4F::WHITE),
			Wait::Create(3.f),
			TintTo::Create(1.f, Color4F::INVISIBLE),
			Wait::Create(5.f)
		})
	);
	
	TopName->RunAction(fadeInAction);
	TopScore->RunAction(fadeInAction->Clone());

	PressEnter->RunAction(Sequence::Create
	({
		Wait::Create(5.f),
		fadeInAction->Clone()
	}));

	auto scoreBoard = ScoreBoard::GetInstance();
	for (int i = 0; i < SCOREBOARD_MAX; ++i)
	{
		auto scoreInfo = scoreBoard->GetScoreInfo(i);

		wchar_t nameStr[256];
		MultiByteToWideChar(CP_ACP, 0, scoreInfo.name.c_str(), -1, nameStr, 256);

		auto name = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 40, nameStr);
		name->SetColorA(0);
		name->SetPosition(TopName->GetPositionX(), TopName->GetPositionY() + (i + 1) * 60);
		this->AddChild(name);

		wchar_t scoreStr[256];
		wsprintf(scoreStr, L"%d", scoreInfo.score);
		auto score = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 40, scoreStr);
		score->SetColorA(0);
		score->SetPosition(TopScore->GetPositionX(), TopScore->GetPositionY() + (i + 1) * 60);
		this->AddChild(score);

		name->RunAction(fadeInAction->Clone());
		score->RunAction(fadeInAction->Clone());
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