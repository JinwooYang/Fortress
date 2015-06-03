#pragma once
const int WINDOW_X = 1280;
const int WINDOW_Y = 720;
const LPCWSTR PROJECT_NAME = L"Geometry Space";
const bool WINDOWED = true;
const bool SHOW_CURSOR_WHEN_FULLSCREEN = false;
const bool CLIP_CURSOR_WHEN_FULLSCREEN = true;

//obj �߰� ���� �α� ����
#define PRINT_OBJ_ADD_DEL_LOG 0


//GlobalData
const float GRAVITY = 0.5f;
const float GROUND_Y = WINDOW_Y - 50.f;