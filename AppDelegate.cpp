#include "DXUT.h"
#include "AppDelegate.h"
#include "TitleScene.h"
#include "ScoreBoard.h"

USING_NS_DX2DX;

AppDelegate::AppDelegate()
{
	ScoreBoard::GetInstance();
}


AppDelegate::~AppDelegate()
{
	ScoreBoard::DestroyInstance();
}

void AppDelegate::AppLaunching()
{
	Director::GetInstance()->RunWithScene(TitleScene::Create());
}