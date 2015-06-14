#include "DXUT.h"
#include "ScoreDialog.h"
#include "GameScene.h"
#include "ScoreBoard.h"

USING_NS_DX2DX;

const int ID_EDIT = 100;

ScoreDialog::ScoreDialog(int score, std::function<void()> callback) :
_Score(score),
_DialogImg(Sprite::Create(LR"(Resources/Images/dialog_image.png)")),
_EditControl(Sprite::Create(LR"(Resources/Images/edit_control.png)")),
_ScoreText(Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 30, L"")),
_NameText(Label::Create(LR"(Resources/Fonts/NanumGothic.ttf)", 30, L"")),
_BtnOK(Button::Create(LR"(Resources/Images/btn_ok.png)")),
_CloseCallBack(callback)
{
	ZeroMemory(_Name, sizeof(_Name));

	this->AddChild(_DialogImg);

	wchar_t str[256];
	wsprintf(str, L"현재 점수 : %d \n 이름을 입력해 주세요. (5자 이내)", score);
	_ScoreText->SetString(str);
	_ScoreText->SetPosition(0, -100);
	this->AddChild(_ScoreText);

	_EditControl->SetPosition(0, 0);
	this->AddChild(_EditControl);

	_NameText->SetPosition(_EditControl->GetPosition());
	_NameText->SetColor(Color4F::BLACK);
	this->AddChild(_NameText);

	_BtnOK->SetClickedCallBack([&](Button* btn)
	{
		OKBtnCallBack();
	});
	_BtnOK->SetPosition(0, 120);
	this->AddChild(_BtnOK);
}


ScoreDialog::~ScoreDialog()
{
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
			if (len < sizeof(_Name) / sizeof(wchar_t))
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