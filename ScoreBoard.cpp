#include "DXUT.h"
#include "ScoreBoard.h"
#include <algorithm>
#include <json\json.h>

SINGLETONE_INSTANCE_INIT(ScoreBoard, nullptr);

ScoreBoard::ScoreBoard()
{
}


ScoreBoard::~ScoreBoard()
{
}


void ScoreBoard::SaveScore()
{
}


void ScoreBoard::LoadScore()
{

}


int ScoreBoard::GetLowestScore()
{
	return _ScoreBoard.back();
}


void ScoreBoard::SubmitScore(int score)
{
	_ScoreBoard[SCOREBOARD_MAX] = score;
	std::sort(_ScoreBoard.begin(), _ScoreBoard.end());
}