#pragma once
#include "../ui/GameBoard.h"
#include "../event/GameEvent.h"
#include "../ai/GameAI.h"
class GameEngine
{
public:
	/*GameEngine(RenderWindow &window,Event &event): matrix(3, vector<GameBoard::ItemType>(3, GameBoard::ItemType::NA)){
		
	}*/
	GameEngine operator=(GameEngine&) = delete;
	static GameEngine& Get();
	static void Init(Vector2u windowSize = Vector2u(1280, 720));
	static void Run();
	static void Reset();

	void UpdateAt(pair<int, int> pos, GameBoard::ItemType type);

	void resolveMouseEvent();
	void Update();
	void RenderUi();
private:
	
	//member variables
	GameBoard* board;
	GameEvent* gEvent;
	GameAI* ai;
	RenderWindow window;
	vector<vector<GameBoard::ItemType>> matrix;
	int counter;
	bool isUserTurn;
	Clock clock;
	pair<bool, Event::MouseButtonEvent> userEventPos;
	Button* reset;

	//member functions
	GameEngine();
	void InitImpl(Vector2u windowSize);
	void RunImpl();
	void ResetImpl();
};


