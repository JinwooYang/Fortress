#include "DXUT.h"
#include "ScoreDialog.h"
#include "GameScene.h"
#include "ScoreBoard.h"

USING_NS_DX2DX;


ScoreDialog::ScoreDialog(int score, std::function<void()> callback) :
_Score(score),
_CloseCallBack(callback)
{
	InitBackImg();

	InitStarImg();

	InitText();

	float elapseTime = 0.f;

	elapseTime = ActionBackImg(elapseTime);
	elapseTime = ActionStarImg(elapseTime);
	elapseTime = ActionText(elapseTime);

	ZeroMemory(_Name, sizeof(_Name));
}


ScoreDialog::~ScoreDialog()
{
}


void ScoreDialog::InitBackImg()
{
	_BackImg = Sprite::Create(LR"(Resources/Images/scoreboard_image.png)");
	_BackImg->SetPosition(WINDOW_X / 2, WINDOW_Y / 2);
	_BackImg->SetScale(0.f);
	this->AddChild(_BackImg);
}


void ScoreDialog::InitStarImg()
{
	for (int i = 0; i < STAR_NUM; ++i)
	{
		_StarEmpty[i] = Sprite::Create(LR"(Resources/Images/star_empty.png)");
		_StarEmpty[i]->SetVisible(false);
		this->AddChild(_StarEmpty[i]);
	}
	_StarEmpty[0]->SetPosition(WINDOW_X / 2 - 200, WINDOW_Y * 0.3f);
	_StarEmpty[1]->SetPosition(WINDOW_X / 2, WINDOW_Y * 0.2f);
	_StarEmpty[2]->SetPosition(WINDOW_X / 2 + 200, WINDOW_Y * 0.3f);

	for (int i = 0; i < STAR_NUM; ++i)
	{
		_StarFull[i] = Sprite::Create(LR"(Resources/Images/star_full.png)");
		_StarFull[i]->SetPosition(_StarEmpty[i]->GetPosition());
		_StarFull[i]->SetScale(0.f);
		this->AddChild(_StarFull[i]);
	}
}


void ScoreDialog::InitText()
{
	wchar_t str[256] = { '\0', };
	_ScoreText = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 70, L"");
	wsprintf(str, L"%d", _Score);
	_ScoreText->SetString(str);
	_ScoreText->SetPosition(WINDOW_X / 2, WINDOW_Y / 2);
	_ScoreText->SetVisible(false);
	this->AddChild(_ScoreText);

	_InputYourNameText = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 40, L"Input Your Name");
	_InputYourNameText->SetPosition(WINDOW_X / 2, WINDOW_Y * 0.7f);
	_InputYourNameText->SetVisible(false);
	this->AddChild(_InputYourNameText);

	_EditControl = Sprite::Create(LR"(Resources/Images/edit_control.png)");
	_EditControl->SetPosition(WINDOW_X / 2, WINDOW_Y * 0.8f);
	_EditControl->SetVisible(false);
	this->AddChild(_EditControl);

	_NameText = Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 40, L"");
	_NameText->SetPosition(_EditControl->GetPosition());
	_NameText->SetColor(Color4F::BLACK);
	_NameText->SetVisible(false);
	this->AddChild(_NameText);

}


float ScoreDialog::ActionBackImg(float waitTime)
{
	_BackImg->RunAction
	(
		Sequence::Create
		({
			Wait::Create(waitTime),
			ScaleTo::Create(0.2f, Point(1.f, 1.f))
		})
	);

	return waitTime + 0.2f;
}


float ScoreDialog::ActionStarImg(float waitTime)
{
	int starNum = 0;

	for (int i = 0; i < STAR_NUM; ++i)
	{
		_StarEmpty[i]->RunAction
		(
			Sequence::Create
			({
				Wait::Create(waitTime),
				CallFunc::Create
				(
					std::bind([](Node* node){ node->SetVisible(true); }, _StarEmpty[i])
				)
			})
		);

		if (_Score > 300 + (i * 300))
		{
			++starNum;
			
			_StarFull[i]->RunAction
			(
				Sequence::Create
				({
					Wait::Create(waitTime + ((i + 1) * 0.2f)),
					ScaleTo::Create(0.2f, Point(1.f, 1.f))
				})
			);
		}
	}

	return waitTime + (starNum * 0.4f);
}


float ScoreDialog::ActionText(float waitTime)
{
	auto visibleAction = [=](Node* node)->Action*
	{
		return 	Sequence::Create
				({
					Wait::Create(waitTime),
					CallFunc::Create
					(
						std::bind([](Node* node){ node->SetVisible(true); }, node)
					)
				});
	};

	_ScoreText->RunAction(visibleAction(_ScoreText));

	_InputYourNameText->RunAction(visibleAction(_InputYourNameText));

	_EditControl->RunAction(visibleAction(_EditControl));

	_NameText->RunAction(visibleAction(_NameText));

	return waitTime + 0.4f;
}

void ScoreDialog::OKBtnCallBack()
{
	if (wcslen(_Name) == 0)
	{
		MessageBox(DXUTGetHWND(), L"이름을 입력해 주세요.", L"경고", MB_OK | MB_ICONWARNING);
	}
	else
	{
		char str[10];
		WideCharToMultiByte(CP_ACP, 0, _Name, -1, str, 10, nullptr, nullptr);
		ScoreBoard::GetInstance()->SubmitScore(str, _Score);
		Director::GetInstance()->ReplaceScene(GameScene::Create());
		_CloseCallBack();
	}
}


void ScoreDialog::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int len = wcslen(_Name);

	switch (msg)
	{
	case WM_CHAR:
		switch (wParam)
		{
		case VK_RETURN:
			OKBtnCallBack();
			break;

		case VK_BACK:
			if (wParam == VK_BACK)
			{
				_Name[len - 1] = '\0';
			}
			break;

		default:
			if (len < 5 - 1)
			{
				_Name[len] = wParam;
				_Name[len + 1] = '\0';
			}			break;
		}

		_NameText->SetString(_Name);
		break;

	default:
		break;
	}
}