#include "GameEngine.h"
#include<iostream>

GameEngine& GameEngine::Get()
{
    static GameEngine instance;
	return instance;
}

void GameEngine::Init(Vector2u windowSize)
{
	Get().InitImpl(windowSize);
}

void GameEngine::Run()
{
    Get().RunImpl();
}

void GameEngine::Reset()
{
    Get().ResetImpl();
}

void GameEngine::UpdateAt(pair<int, int> pos, GameBoard::ItemType type)
{
	if (pos.first == -1) return;
	matrix[pos.first][pos.second] = type;
    counter++;
    isUserTurn = !isUserTurn;
}

void GameEngine::resolveMouseEvent()
{
    Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case Event::Closed:
            window.close();
            break;

        case Event::MouseButtonPressed:
            if (gEvent->GetIsCompleted() || counter == 9) {
                if (reset->isClick(event)) {
                    ResetImpl();
                }
            }
            else if (!isUserTurn) continue;
            userEventPos = { true,event.mouseButton };
            break;

        case Event::Resized:
            gEvent->Update(event.size);
            break;
        
        default:
            break;
        }
    }
}

void GameEngine::Update()
{
    if (isUserTurn) {
        if (!userEventPos.first) return;
        UpdateAt(gEvent->GetBlock(userEventPos.second,matrix), GameBoard::ItemType::X);
        userEventPos = { false , {} };
    }
    else {
        if (gEvent->GetIsCompleted()) return;
       // clock.restart();
       // while (clock.getElapsedTime().asMilliseconds() != 500); //wait 1s
        UpdateAt(ai->PredictNext(matrix, GameBoard::ItemType::O), GameBoard::ItemType::O);
    }
}

void GameEngine::RenderUi()
{
    window.clear();


    board->DrawBoard(window);
    gEvent->HoverEffect(window, matrix);
    board->DrawItems(window, matrix);
    board->DrawWinLine(window, gEvent->isGameWin(matrix));
    if (gEvent->GetIsCompleted()) {
        auto p = gEvent->getWinPair();
        //cout << p.first.first << " " << p.first.second << " : " << p.second.first << " " << p.second.second << endl;
        board->DrawWinText(window, matrix[p.first.first][p.first.second]);
        reset->setText("Reset");
        reset->setSize({ 200,80 });
        reset->setColor(Color::Blue);
        reset->setTextSize(50);
        reset->setPosition({ (1280.0f / window.getSize().x) * (window.getSize().x - reset->getSize().x) * 0.8f,300 });
        reset->attachTo(window);
    }
    else if (counter == 9) {
        board->DrawDrawText(window);
        reset->setText("Reset");
        reset->setSize({ 200,80 });
        reset->setColor(Color::Blue);
        reset->setTextSize(50);
        reset->setPosition({ (1280.0f / window.getSize().x) * (window.getSize().x - reset->getSize().x) * 0.8f,300 });
        reset->attachTo(window);
    }

    window.display();
}

GameEngine::GameEngine(): window(VideoMode(1280, 720), "Tic Tac Toe"),matrix(3,vector<GameBoard::ItemType>(3,GameBoard::ItemType::NA))
{
    board = new GameBoard();
	gEvent = new GameEvent();
    ai = new GameAI();
    reset = new Button(window);
}

void GameEngine::InitImpl(Vector2u windowSize)
{
    window.create(VideoMode(windowSize.x, windowSize.y), "Tic Tac Toe");
	
	board->SetSize(500, 500);
	board->ShowGrid(true);
	board->CenteredAlign(false,true);
    board->SetMargin(10, 0);
	board->Init(windowSize);

	gEvent->Init(*board);

    ai->SetGameMode(GameAI::GameMode::HARD);

    isUserTurn = true;
    counter = 0;
}

void GameEngine::RunImpl()
{
    while (window.isOpen()) {

        resolveMouseEvent();

        Update();
        RenderUi();

    }
}

void GameEngine::ResetImpl()
{
    for (auto& m : matrix) {
        for (auto& n : m) {
            n = GameBoard::ItemType::NA;
        }
    }
    counter = 0;
    isUserTurn = true;
    gEvent->reset();
}

