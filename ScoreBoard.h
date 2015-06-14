#pragma once
#include "dx2dx.h"
#include <array>
#include <json\json.h>

const int SCOREBOARD_MAX = 10;

struct ScoreInfo
{
	std::string name;
	int score;
};

class ScoreBoard
{

private:
	SINGLETONE(ScoreBoard);

	Json::Value _Root;

	std::array<ScoreInfo, SCOREBOARD_MAX> _ScoreBoard;

	void LoadScore();
	void SaveScore();

public:

	int GetLowestScore();
	void SubmitScore(std::string name, int score);
	ScoreInfo GetScoreInfo(int rank);
};

