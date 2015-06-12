#include "DXUT.h"
#include "ScoreBoard.h"
#include <algorithm>
#include <json\json.h>
#include <fstream>

SINGLETONE_INSTANCE_INIT(ScoreBoard, nullptr);

ScoreBoard::ScoreBoard()
{
	for (int i = 0; i < SCOREBOARD_MAX; ++i)
	{
		_ScoreBoard[i].name = "Unknown";
		_ScoreBoard[i].score = 0;
	}
}


ScoreBoard::~ScoreBoard()
{
	SaveScore();
}


void ScoreBoard::LoadScore()
{

}


void ScoreBoard::SaveScore()
{
	for (int i = 0; i < SCOREBOARD_MAX; ++i)
	{
		Json::Value scoreInfo;

		scoreInfo["name"] = _ScoreBoard[i].name.c_str();
		scoreInfo["score"] = _ScoreBoard[i].score;

		_Root["ScoreBoard"].append(scoreInfo);
	}

	Json::StyledWriter writer;
	auto str = writer.write(_Root);

	std::ofstream ofs("scoreBoard.json");

	bool ofsOpenSuccess = ofs.is_open();

	assert(ofsOpenSuccess && "Output scoreBoard.json is Failed.");

	if (ofsOpenSuccess)
	{
		ofs << str.c_str();
		ofs.close();
	}
}


int ScoreBoard::GetLowestScore()
{
	return _ScoreBoard[SCOREBOARD_MAX - 1].score;
}


void ScoreBoard::SubmitScore(int score)
{
	_ScoreBoard[SCOREBOARD_MAX - 1].score = score;
	std::sort(_ScoreBoard.begin(), _ScoreBoard.end(), [](ScoreInfo a, ScoreInfo b)->bool
	{
		return (a.score > b.score);
	});
}