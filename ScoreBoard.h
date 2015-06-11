#pragma once
#include "dx2dx.h"
#include <array>

const int SCOREBOARD_MAX = 10;

class ScoreBoard
{
private:
	SINGLETONE(ScoreBoard);

	std::array<int, SCOREBOARD_MAX> _ScoreBoard;

	void SaveScore();

public:
	void LoadScore();

	int GetLowestScore();
	void SubmitScore(int score);
};

