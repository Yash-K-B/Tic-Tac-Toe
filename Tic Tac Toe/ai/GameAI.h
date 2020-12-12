#pragma once
#include "../ui/GameBoard.h"

class GameAI
{
public:
	enum class GameMode { NOOB, EASY, MEDUIM, HARD };
	GameAI() {
		srand(time(0));
		gameMode = GameMode::NOOB;
	}
	void SetGameMode(GameMode mode);
	pair<int,int> PredictNext(vector<vector<GameBoard::ItemType>>& matrix, GameBoard::ItemType type);
	pair<int, int> predictNoob(vector<vector<GameBoard::ItemType>>& matrix, GameBoard::ItemType type);
	//pair<int, int> predictEasy(vector<vector<GameBoard::ItemType>>& matrix,GameBoard::ItemType type);
	pair<int, int> predictMedium(vector<vector<GameBoard::ItemType>>& matrix, GameBoard::ItemType type);
	pair<int, int> predictHard(vector<vector<GameBoard::ItemType>>& matrix, GameBoard::ItemType type);
	vector<vector<tuple<int, int, int>>> countItems(vector<vector<GameBoard::ItemType>>& matrix);
private:
	enum Matrix { ROW, COL, DIAG };
	enum Item { NA, X, O };
	GameMode gameMode;

	int minmax(vector<vector<GameBoard::ItemType>> matrix,bool isMax,int level,GameBoard::ItemType& type);
	int minmaxMedium(vector<vector<GameBoard::ItemType>> matrix, bool isMax, int level, GameBoard::ItemType& type);
	int score(vector<vector<GameBoard::ItemType>>& matrix, GameBoard::ItemType& type);
};

