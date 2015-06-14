#include "DXUT.h"
#include "ScoreBoard.h"
#include <algorithm>
#include <json\json.h>
#include <fstream>

SINGLETONE_INSTANCE_INIT(ScoreBoard, nullptr);

bool ReadFromFile(const char* filename, char* buffer, int len)
{
	FILE* r = fopen(filename, "rb");

	if (NULL == r)
		return false;

	size_t fileSize = fread(buffer, 1, len, r);
	fclose(r);

	return true;
}

ScoreBoard::ScoreBoard()
{
	for (int i = 0; i < SCOREBOARD_MAX; ++i)
	{
		_ScoreBoard[i].name = "Unknown";
		_ScoreBoard[i].score = 0;
	}
	LoadScore();
}


ScoreBoard::~ScoreBoard()
{
	SaveScore();
}


void ScoreBoard::LoadScore()
{
	char str[2048];

	if (ReadFromFile("scoreBoard.json", str, 2048))
	{
		Json::Reader reader;
		Json::Value root;

		reader.parse(str, root);

		Json::Value array = root["ScoreBoard"];

		for (int i = 0; i < array.size(); ++i)
		{
			_ScoreBoard[i].name = array[i].get("name", "Unknown").asString();
			_ScoreBoard[i].score = array[i].get("score", 0).asInt();
		}
	}
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


void ScoreBoard::SubmitScore(std::string name, int score)
{
	_ScoreBoard[SCOREBOARD_MAX - 1].name = name;
	_ScoreBoard[SCOREBOARD_MAX - 1].score = score;

	std::sort(_ScoreBoard.begin(), _ScoreBoard.end(), [](ScoreInfo a, ScoreInfo b)->bool
	{
		return (a.score > b.score);
	});
}


ScoreInfo ScoreBoard::GetScoreInfo(int rank)
{
	assert(0 <= rank && rank < SCOREBOARD_MAX && "랭크가 최대 순위표 범위를 벗어남.");

	return _ScoreBoard[rank];
}