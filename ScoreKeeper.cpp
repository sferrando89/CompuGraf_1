#include "ScoreKeeper.h"
#include <iostream>

ScoreKeeper* ScoreKeeper::instance = NULL;

ScoreKeeper::ScoreKeeper()
{

}

ScoreKeeper* ScoreKeeper::GetInstance()
{
	if (!instance)
	{
		instance = new ScoreKeeper();
	}
	return instance;
}

int ScoreKeeper::getScore()
{
	return score;
}

void ScoreKeeper::increaseScore()
{
	score++;
}

void ScoreKeeper::resetScore()
{
	score = 0;
}