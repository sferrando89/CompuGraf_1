#pragma once
class ScoreKeeper
{
	private:
		ScoreKeeper();
		int score = 0;
		static ScoreKeeper* instance;
	public:
		static ScoreKeeper* GetInstance();

		int getScore();
		void increaseScore();
		void resetScore();

};

