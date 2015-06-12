#pragma once
#include "dx2dx.h"
#include <array>
#include <json\json.h>

const int SCOREBOARD_MAX = 10;

class ScoreBoard
{
	struct ScoreInfo
	{
		std::string name;
		int score;
	};

private:
	SINGLETONE(ScoreBoard);

	Json::Value _Root;

	std::array<ScoreInfo, SCOREBOARD_MAX> _ScoreBoard;

	void LoadScore();
	void SaveScore();

public:

	int GetLowestScore();
	void SubmitScore(int score);
};

