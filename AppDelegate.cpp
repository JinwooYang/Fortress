#include "DXUT.h"
#include "AppDelegate.h"
#include "TitleScene.h"

USING_NS_DX2DX;

AppDelegate::AppDelegate()
{
}


AppDelegate::~AppDelegate()
{
}

void AppDelegate::AppLaunching()
{
	Director::GetInstance()->RunWithScene(TitleScene::Create());
}