#include "CornersManager.h"



CornersManager::CornersManager()
{
	_isGameFinished = false;
}


CornersManager::~CornersManager()
{
	delete this->board;
	delete this->player1;
	delete this->player2;
}

bool CornersManager::Start()
{
	std::string playerName;
	unsigned int maxTurns;
	std::cout << "Number of turns: ";
	std::cin >> maxTurns;
	if (maxTurns < 2) {
		return false;
	}

	this->board = new CornersBoard(maxTurns-1);
	this->player1 = new CornersPlayer();
	this->player2 = new CornersPlayer();
	std::cin.ignore();

	std::cout << "Player 1 (B) name: ";
	std::getline(std::cin, playerName);
	player1->SetupPlayer(playerName, CellType_B);

	std::cout << "Player 2 (W) name: ";
	std::getline(std::cin, playerName);
	player2->SetupPlayer(playerName, CellType_W);

	player1->SetBoard(this->board);
	player2->SetBoard(this->board);

	currentPlayer = player1;

	return true;
}

void CornersManager::ShowBoard()
{
	std::cout << "Turn #" << board->GetCurrentTurn() << std::endl;
	this->board->Show();
	std::cout << std::endl;
}

void CornersManager::MakeMove()
{
	ShowBoard();
	this->board->SetAvailableMoves(currentPlayer->GetType());
	while (!currentPlayer->MakeMove()) {
		std::cout << "bad move" << std::endl;
	}
	if (this->board->CheckEndCondition()) {
		if (this->board->GetWinner() == 0) {
			std::cout << "DRAW" << std::endl;
		}
		else {
			if (this->board->GetWinner() == CellType_B) {
				std::cout << "Winner is B" << std::endl;
			}
			if (this->board->GetWinner() == CellType_W) {
				std::cout << "Winner is W" << std::endl;
			}
		}
		this->_isGameFinished = true;
		ShowBoard();
		return;
	}
	currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool CornersManager::isGameFinished()
{
	return _isGameFinished;
}
