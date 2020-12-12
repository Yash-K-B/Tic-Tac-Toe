#pragma once
#include "../ui/GameBoard.h"
class GameEvent
{

public:
	GameEvent() {
		isCompleted = false;
		winPair = { {-1,-1},{-1,-1} };
	}
	void Init(GameBoard &board);
	void Update(Event::SizeEvent sizeEvent);
	void HoverEffect(RenderWindow& window, vector<vector<GameBoard::ItemType>>& matrix,Color color = Color(0,210,12,30));
	pair<int, int> GetBlock(Event::MouseButtonEvent mouseButton, vector<vector<GameBoard::ItemType>>& matrix);
	pair<pair<int, int>, pair<int, int>> isGameWin(vector<vector<GameBoard::ItemType>>& matrix);
	bool GetIsCompleted();
	pair<pair<int, int>, pair<int, int>> getWinPair();
	void reset();
private:
	pair<Vector2f, Vector2f> blocks[3][3];
	bool isCompleted;
	float scaleX, scaleY;
	pair<pair<int, int>, pair<int, int>> winPair;
};

