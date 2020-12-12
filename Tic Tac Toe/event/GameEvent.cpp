#include "GameEvent.h"
#include<iostream>
void GameEvent::Init(GameBoard &board)
{
	//font.loadFromFile("fonts/Monotype Corsiva.ttf");
	scaleX = 1.0f;
	scaleY = 1.0f;
	float verticalSegment = board.GetHeight() / 3.0f, horizontalSegment = board.GetWidth() / 3.0f;
	Vector2f boardPosition = board.getPosition();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			blocks[i][j] = make_pair(Vector2f(boardPosition.x + horizontalSegment * j,boardPosition.y + verticalSegment * i),Vector2f(boardPosition.x + horizontalSegment * (j+1), boardPosition.y + verticalSegment * (i+1)));
		}
	}
}

void GameEvent::Update(Event::SizeEvent sizeEvent)
{
	scaleX = 1280.0f / sizeEvent.width;
	scaleY = 720.0f / sizeEvent.height;
}

void GameEvent::HoverEffect(RenderWindow& window, vector<vector<GameBoard::ItemType>>& matrix,Color color)
{

	if (isCompleted) return;
	
	float x = Mouse::getPosition(window).x * scaleX, y = Mouse::getPosition(window).y * scaleY;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if ((matrix[i][j] == GameBoard::ItemType::NA) && blocks[i][j].first.x <= x && x < blocks[i][j].second.x && blocks[i][j].first.y <= y && y < blocks[i][j].second.y) {
				RectangleShape shape(Vector2f(blocks[i][j].second.x - blocks[i][j].first.x, blocks[i][j].second.y - blocks[i][j].first.y));
				shape.setPosition(blocks[i][j].first);
				shape.setFillColor(color);
				window.draw(shape);
				break;
			}
		}
	}
}

pair<int, int> GameEvent::GetBlock(Event::MouseButtonEvent mouseButton, vector<vector<GameBoard::ItemType>>& matrix)
{
	if (isCompleted) return { -1,-1 };
	float x = mouseButton.x * scaleX;
	float y = mouseButton.y * scaleY;
	int row = -1, col = -1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (blocks[i][j].first.x <= x && x < blocks[i][j].second.x && blocks[i][j].first.y <= y && y < blocks[i][j].second.y) {
				if (matrix[i][j] == GameBoard::ItemType::NA) {
					row = i;
					col = j;
				}
				break;
			}
		}
	}
	return pair<int, int>({row,col});
}

pair<pair<int, int>, pair<int, int>> GameEvent::isGameWin(vector<vector<GameBoard::ItemType>>& matrix)
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
			isCompleted = true;
			winPair =  { {i,0},{i,2} };
			return winPair;
		}

		if (colWin) {
			isCompleted = true;
			winPair = { {0,i},{2,i} };
			return winPair;
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
		isCompleted = true;
		winPair = { {0,0},{2,2} };
		return winPair;
	}  

	if (diag2Win) {
		isCompleted = true;
		winPair = { {0,2},{2,0} };
		return winPair;
	}

	return winPair;
}

bool GameEvent::GetIsCompleted()
{
	return isCompleted;
}

pair<pair<int, int>, pair<int, int>> GameEvent::getWinPair()
{
	return winPair;
}

void GameEvent::reset()
{
	isCompleted = false;
	winPair = { {-1,-1},{-1,-1} };
}
