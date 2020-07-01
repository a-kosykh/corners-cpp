#include "CornersPlayer.h"



CornersPlayer::CornersPlayer()
{
}


CornersPlayer::~CornersPlayer()
{
}

void CornersPlayer::SetupPlayer(std::string name, CellType ct)
{
	this->name = name;
	this->cellType = ct;
}

CellType CornersPlayer::GetType()
{
	return this->cellType;
}

void CornersPlayer::SetBoard(CornersBoard * board)
{
	this->board = board;
}

bool CornersPlayer::MakeMove()
{
	unsigned int start_row, start_col, end_row, end_col;
	std::string strCellType = (this->cellType == CellType_B) ? "B" : "W";
	std::cout << "Player " << this->name << " (" << strCellType << ")" << " your turn..." << std::endl;
	std::cout << "Enter start_row: ";
	std::cin >> start_row;
	std::cout << "Enter start_column: ";
	std::cin >> start_col;
	std::cout << "Enter end_row: ";
	std::cin >> end_row;
	std::cout << "Enter end_column: ";
	std::cin >> end_col;
	
	return board->SetCell(start_row, start_col, end_row, end_col, this->cellType);
}
