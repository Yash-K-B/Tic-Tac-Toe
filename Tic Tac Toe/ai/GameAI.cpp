#include "GameAI.h"

void GameAI::SetGameMode(GameMode mode)
{
	this->gameMode = mode;
}

pair<int, int> GameAI::PredictNext(vector<vector<GameBoard::ItemType>>& matrix, GameBoard::ItemType type)
{
	switch (gameMode) {
	case GameMode::NOOB:
		return predictNoob(matrix,type);
	//case GameMode::EASY:
	///	return predictEasy(matrix,type);
	case GameMode::MEDUIM:
		return predictMedium(matrix,type);
	case GameMode::HARD:
		return predictHard(matrix,type);

	}
	
}

pair<int, int> GameAI::predictNoob(vector<vector<GameBoard::ItemType>>& matrix, GameBoard::ItemType type)
{
	vector<pair<int, int>> res;
	res.reserve(9);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] == GameBoard::ItemType::NA)
				res.emplace_back(i, j);
		}
	}
	time_t t = time(0);
	srand(t);
	if (res.size() == 0) return { -1,-1 };
	int val = rand() % res.size();
	return res[val];
}

pair<int, int> GameAI::predictMedium(vector<vector<GameBoard::ItemType>>& matrix,GameBoard::ItemType type)
{

	int levelCounter = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] != GameBoard::ItemType::NA)
				levelCounter++;
		}
	}
	vector<pair<int, int>> winPairs, drawPairs;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] == GameBoard::ItemType::NA) {
				matrix[i][j] = type;
				int res = minmaxMedium(matrix, false, levelCounter + 1, type);
				if (res == 1) {
					winPairs.push_back({ i,j });
				}
				if (res == 0) {
					drawPairs.push_back({ i,j });
				}
				matrix[i][j] = GameBoard::ItemType::NA;
			}
		}
	}
	if (!winPairs.empty())
		return winPairs[rand() % winPairs.size()];
	else if (!drawPairs.empty())
		return drawPairs[rand() % drawPairs.size()];
	return predictNoob(matrix, type);
}

pair<int, int> GameAI::predictHard(vector<vector<GameBoard::ItemType>>& matrix, GameBoard::ItemType type)
{
	/*int sc = 0;*/
	int levelCounter = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] != GameBoard::ItemType::NA)
				levelCounter++;
		}
	}
	vector<pair<int, int>> winPairs,drawPairs;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] == GameBoard::ItemType::NA) {
					matrix[i][j] = type;
					int res = minmax(matrix, false,levelCounter+1, type);
					if ( res == 1) {
						winPairs.push_back({ i,j });
					}
					if (res == 0) {
						drawPairs.push_back({ i,j });
					}
					matrix[i][j] = GameBoard::ItemType::NA;
			}
		}
	}
	if (!winPairs.empty())
		return winPairs[rand() % winPairs.size()];
	else if (!drawPairs.empty())
		return drawPairs[rand() % drawPairs.size()];
	return predictNoob(matrix,type);
}

vector<vector<tuple<int, int, int>>> GameAI::countItems(vector<vector<GameBoard::ItemType>>& matrix)
{
	vector<vector<tuple<int, int, int>>> result(3);
	//row
	int Xcount, Ocount, NAcount;
	for (int i = 0; i < 3; i++) {
		Xcount = 0;
		Ocount = 0;
		NAcount = 0;
		for (int j = 0; j < 3; j++) {
			switch (matrix[i][j]){
			case GameBoard::ItemType::NA:
				NAcount++;
				break;
			case GameBoard::ItemType::O:
				Ocount++;
				break; 
			case GameBoard::ItemType::X:
				Xcount++;
				break;
			}
		}
		result[ROW].push_back(make_tuple(NAcount, Xcount, Ocount));
	}

	//col
	for (int i = 0; i < 3; i++) {
		Xcount = 0;
		Ocount = 0;
		NAcount = 0;
		for (int j = 0; j < 3; j++) {
			switch (matrix[j][i]) {
			case GameBoard::ItemType::NA:
				NAcount++;
				break;
			case GameBoard::ItemType::O:
				Ocount++;
				break;
			case GameBoard::ItemType::X:
				Xcount++;
				break;
			}
		}
		result[COL].push_back(make_tuple(NAcount, Xcount, Ocount));
	}

	Xcount = 0;
	Ocount = 0;
	NAcount = 0;
	for (int i = 0; i < 3; i++) {
		switch (matrix[i][i]) {
		case GameBoard::ItemType::NA:
			NAcount++;
			break;
		case GameBoard::ItemType::O:
			Ocount++;
			break;
		case GameBoard::ItemType::X:
			Xcount++;
			break;
		}
	}
	result[DIAG].push_back(make_tuple(NAcount, Xcount, Ocount));

	Xcount = 0;
	Ocount = 0;
	NAcount = 0;
	for (int i = 0,j=2; i < 3; i++,j--) {
		switch (matrix[i][j]) {
		case GameBoard::ItemType::NA:
			NAcount++;
			break;
		case GameBoard::ItemType::O:
			Ocount++;
			break;
		case GameBoard::ItemType::X:
			Xcount++;
			break;
		}
	}
	result[DIAG].push_back(make_tuple(NAcount, Xcount, Ocount));

	return result;
}

int GameAI::minmax(vector<vector<GameBoard::ItemType>> matrix, bool isMax,int level, GameBoard::ItemType& type)
{

	int sc = score(matrix,type);
	if (sc != 0) return sc;
	if (level == 9) return sc;
	sc = isMax ? -2 : 2;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] == GameBoard::ItemType::NA) {
				if (isMax) {
					matrix[i][j] = type;
					sc = max(sc, minmax(matrix, false,level+1, type));
					matrix[i][j] = GameBoard::ItemType::NA;
				}
				else {
					matrix[i][j] = (type == GameBoard::ItemType::X) ? GameBoard::ItemType::O : GameBoard::ItemType::X;
					sc = min(sc, minmax(matrix, true,level+1, type));
					matrix[i][j] = GameBoard::ItemType::NA;
				}
			}
		}
	}
	return sc;
}


int GameAI::minmaxMedium(vector<vector<GameBoard::ItemType>> matrix, bool isMax,int level, GameBoard::ItemType& type)
{

	int sc = score(matrix,type);
	if (sc != 0) return sc;
	if (level > 9) return sc;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] == GameBoard::ItemType::NA) {
				if (isMax) {
					matrix[i][j] = type;
					sc = max(sc, minmaxMedium(matrix, false,level+1, type));
					matrix[i][j] = GameBoard::ItemType::NA;
				}
				else {
					matrix[i][j] = (type == GameBoard::ItemType::X) ? GameBoard::ItemType::O : GameBoard::ItemType::X;
					sc = min(sc, minmaxMedium(matrix, true,level+1, type));
					matrix[i][j] = GameBoard::ItemType::NA;
				}
			}
		}
	}
	return sc;
}



int GameAI::score(vector<vector<GameBoard::ItemType>>& matrix, GameBoard::ItemType& type)
{

	for (int i = 0; i < 3; i++) {
		bool colWin = true;   //col check
		bool rowWin = true;   //row check
		for (int j = 1; j < 3; j++) {
			if (matrix[i][j] == GameBoard::ItemType::NA || matrix[i][j - 1] == GameBoard::ItemType::NA || matrix[i][j] != matrix[i][j - 1])
				rowWin = false;
			if (matrix[j][i] == GameBoard::ItemType::NA || matrix[j - 1][i] == GameBoard::ItemType::NA || matrix[j][i] != matrix[j - 1][i])
				colWin = false;

		}
		if (rowWin) {
			return (type == matrix[i][0]) ? 1 : -1;
		}

		if (colWin) {
			return (type == matrix[0][i]) ? 1 : -1;
		}
	}

	bool diag1Win = true;
	bool diag2Win = true;
	for (int i = 1; i < 3; i++) {
		if (matrix[i][i] == GameBoard::ItemType::NA || matrix[i - 1][i - 1] == GameBoard::ItemType::NA || matrix[i][i] != matrix[i - 1][i - 1])
			diag1Win = false;

		if (matrix[i][2 - i] == GameBoard::ItemType::NA || matrix[i - 1][3 - i] == GameBoard::ItemType::NA || matrix[i][2 - i] != matrix[i - 1][3 - i])
			diag2Win = false;
	}

	if (diag1Win) {
		return (type == matrix[0][0]) ? 1 : -1;
	}

	if (diag2Win) {
		return (type == matrix[0][2]) ? 1 : -1;
	}

	return 0;
}


