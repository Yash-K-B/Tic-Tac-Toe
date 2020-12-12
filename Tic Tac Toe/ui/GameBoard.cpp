
#include "GameBoard.h"

#include<iostream>

void GameBoard::CenteredAlign(bool centerHorizontal, bool centerVertical)
{
	this->isCenteredAlignHoriz = centerHorizontal;
	this->isCenteredAlignVert = centerVertical;
}

void GameBoard::SetMargin(int percentStart, int percentTop)
{
	marginLeft = percentStart;
	marginTop = percentTop;
}

void GameBoard::Init(Vector2u windowSize)
{

	width = (windowSize.x / 1280.0f) * 500;
	height = (windowSize.y / 720.0f) * 500;


	boardPositionX = 0;
	boardPositionY = 0;
	if (isCenteredAlignHoriz) {
		boardPositionX = (windowSize.x - width) / 2.0f;
	}
	else if(isCenteredAlignVert)
	{
		boardPositionY = (windowSize.y - height) / 2.0f;
	}
	
	if (marginLeft != 0.0f) {
		boardPositionX += windowSize.x * (marginLeft / 100);
	}

	if (marginTop != 0.0f) {
		boardPositionX += windowSize.y * (marginTop / 100);
	}

	font.loadFromFile("fonts/QuartzoBold.ttf");
	text.setFont(font);
	text.setCharacterSize(80);
	text.setString("H");

	float horizontalSegment = (width / 3.0f);
	float verticalSegment = (height / 3.0f);

	float horizontalOffset = ((horizontalSegment - text.getGlobalBounds().width) / 2.0f) - 10;
	float verticalOffset = ((verticalSegment - text.getGlobalBounds().height) / 2.0f) - 20;
	for (int i = 0; i < 9; i++) {
		float x = boardPositionX + (horizontalSegment * (i % 3)) + horizontalOffset;
		float y = boardPositionY + (verticalSegment * (i / 3)) + verticalOffset;
		positions[i / 3][i % 3] = Vector2f(x, y);
	}

	for (int i = 0; i < 3; i++) {
		//rows
		rowWinLines[i] = make_pair(Vector2f(boardPositionX, boardPositionY + (verticalSegment * i) + verticalSegment / 2.0f), Vector2f(boardPositionX + width, boardPositionY + (verticalSegment * i) + verticalSegment / 2.0f));
		//cols
		colWinLines[i] = make_pair(Vector2f(boardPositionX + (horizontalSegment * i) + horizontalSegment / 2.0f, boardPositionY), Vector2f(boardPositionX + (horizontalSegment * i) + horizontalSegment / 2.0f, boardPositionY + height));
	}

	//diagonal lines
	diagonalWinLines[0] = make_pair(Vector2f(boardPositionX, boardPositionY), Vector2f(boardPositionX + width, boardPositionY + height));
	diagonalWinLines[1] = make_pair(Vector2f(boardPositionX + width, boardPositionY), Vector2f(boardPositionX, boardPositionY + height));

}

void GameBoard::ShowGrid(bool isEnabled)
{
	this->gridEnabled = isEnabled;
}

void GameBoard::DrawGrid(RenderWindow& window)
{
	//Vertical Lines
	for (int i = 1; i < 3; i++) {
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(boardPositionX + ((width / 3) * i), boardPositionY)),
			sf::Vertex(sf::Vector2f(boardPositionX + ((width / 3) * i), boardPositionY + height))
		};

		window.draw(line, 2, sf::Lines);

	}

	//Horizontal Lines
	for (int j = 1; j < 3; j++) {
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(boardPositionX , boardPositionY + ((height / 3) * j))),
			sf::Vertex(sf::Vector2f(boardPositionX + width , boardPositionY + +((height / 3) * j)))
		};

		window.draw(line, 2, sf::Lines);
	}
}

void GameBoard::DrawBoard(RenderWindow& window)
{

	if (gridEnabled)
		DrawGrid(window);

}

void GameBoard::DrawItems(RenderWindow& window, vector<vector<ItemType>>& matrix)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			switch (matrix[i][j]) {
			case ItemType::X:
				DrawX(window, i, j);
				break;
			case ItemType::O:
				DrawO(window, i, j);
				break;
			default:
				break;
			}
		}
	}
}

void GameBoard::DrawX(RenderWindow& window, int row, int col)
{
	float x = positions[row][col].x;
	float y = positions[row][col].y;
	Text textX = text;
	textX.setString("X");
	textX.setPosition(x, y);
	window.draw(textX);
}

void GameBoard::DrawO(RenderWindow& window, int row, int col)
{
	float x = positions[row][col].x;
	float y = positions[row][col].y;
	Text textO = text;
	textO.setString("O");
	textO.setPosition(x, y);
	window.draw(textO);
}

void GameBoard::DrawWinLine(RenderWindow& window, pair<pair<int, int>, pair<int, int>> ln)
{
	if (ln.first.first == -1) return;

	if (ln.first.first == ln.second.first) {	//row win line
		DrawLine(window, rowWinLines[ln.first.first]);
	}
	else if (ln.first.second == ln.second.second) { // col win line
		DrawLine(window, colWinLines[ln.first.second]);
	}
	else if (ln.first.first == ln.first.second && ln.second.first == ln.second.second) { // diagonal 1
		DrawLine(window, diagonalWinLines[0]);
	}
	else if (ln.first.first == ln.second.second && ln.first.second == ln.second.first) { //diagonal 2
		DrawLine(window, diagonalWinLines[1]);
	}
}

void GameBoard::DrawLine(RenderWindow& window, pair<Vector2f, Vector2f>& line)
{
	sf::Vertex points[] =
	{
		sf::Vertex(line.first,Color::Green),
		sf::Vertex(line.second,Color::Green)
	};

	window.draw(points, 2, sf::Lines);
}

void GameBoard::DrawWinText(RenderWindow& window, ItemType type)
{
	string s = (type == ItemType::X) ? "X" : "O";
	Text drawText(s + " Win", font, 80);
	drawText.setPosition((1280.0f / window.getSize().x) * (window.getSize().x - drawText.getGlobalBounds().width) * 0.8f, boardPositionY);
	window.draw(drawText);
}


void GameBoard::DrawDrawText(RenderWindow &window)
{
	Text drawText("Game Draw", font, 80);
	drawText.setPosition((1280.0f/ window.getSize().x) * (window.getSize().x - drawText.getGlobalBounds().width)*0.8f, boardPositionY);
	window.draw(drawText);
	
}

void GameBoard::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

int GameBoard::GetHeight() {
	return height;
}

int GameBoard::GetWidth() {
	return width;
}

Vector2f GameBoard::getPosition()
{
	return Vector2f(boardPositionX, boardPositionY);
}
