#pragma once

#include<SFML/Graphics.hpp>
#include "Button.h"

using namespace std;
using namespace sf;
class GameBoard
{
public:
	enum class ItemType { NA, X, O };
	GameBoard() :height(400), width(400), font(), text() {
		gridEnabled = false;
		boardPositionX = 0;
		boardPositionY = 0;
		marginLeft = 0;
		marginTop = 0;
	}
	GameBoard(int width, int height) :height(height), width(width), font(), text(){
		gridEnabled = false;
		boardPositionX = 0;
		boardPositionY = 0;
		marginLeft = 0;
		marginTop = 0;
	}
	void CenteredAlign(bool centerHorizontal,bool centerVertical);
	void SetMargin(int percentStart, int percentTop);
	void Init(Vector2u windowSize);
	void ShowGrid(bool isEnabled);
	void DrawGrid(RenderWindow& window);
	void DrawBoard(RenderWindow& window);
	void DrawItems(RenderWindow& window, vector<vector<ItemType>>& matrix);
	void DrawX(RenderWindow&, int, int);
	void DrawO(RenderWindow&, int, int);
	void DrawWinLine(RenderWindow& window, pair<pair<int, int>, pair<int, int>>);
	void DrawLine(RenderWindow& window, pair<Vector2f, Vector2f>& line);
	void DrawWinText(RenderWindow& window,ItemType type);
	void DrawDrawText(RenderWindow& window);
	void SetSize(int width, int height);
	int GetHeight();
	int GetWidth();
	Vector2f getPosition();

private:
	int height, width;
	float boardPositionX, boardPositionY;
	float marginLeft, marginTop;
	Font font;
	Vector2f positions[3][3];
	pair<Vector2f, Vector2f> rowWinLines[3], colWinLines[3], diagonalWinLines[2];
	bool gridEnabled, isCenteredAlignHoriz, isCenteredAlignVert;
	Text text;

};