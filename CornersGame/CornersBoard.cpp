#include "CornersBoard.h"



void CornersBoard::AddPossibleMoves_(int oldPos, int newPos, 
	CellType type)
{
	CornersBoard* tempBoard = new CornersBoard(this);
	tempBoard->SetCell_(oldPos / boardSize, oldPos % boardSize,
		newPos / boardSize, newPos % boardSize, type);
	int old_x = oldPos / boardSize;
	int old_y = oldPos % boardSize;
	int new_x = newPos / boardSize;
	int new_y = newPos % boardSize;

	if (oldPos == newPos) {
		// UP
		if (new_x - 1 >= 0) {
			if ((cells[new_x - 1][new_y] == CellType_Empty))
				this->_availableMoves.at(oldPos).insert((new_x - 1) * boardSize + (new_y));
			else {
				if (new_x - 2 >= 0) {
					if ((cells[new_x - 2][new_y] == CellType_Empty))
						if (this->_availableMoves.at(oldPos).insert((new_x - 2) * boardSize + (new_y)).second)
							AddPossibleMoves_(oldPos, (new_x - 2) * boardSize + new_y, type);
				}
			}
		}
		// DOWN
		if (new_x + 1 <= 7) {
			if ((cells[new_x + 1][new_y] == CellType_Empty))
				this->_availableMoves.at(oldPos).insert((new_x + 1) * boardSize + (new_y));
			else {
				if (new_x + 2 <= 7) {
					if ((cells[new_x + 2][new_y] == CellType_Empty))
						if (this->_availableMoves.at(oldPos).insert((new_x + 2) * boardSize + (new_y)).second)
							AddPossibleMoves_(oldPos, (new_x + 2) * boardSize + new_y, type);
				}
			}
		}
		// LEFT
		if (new_y - 1 >= 0) {
			if ((cells[new_x][new_y - 1] == CellType_Empty))
				this->_availableMoves.at(oldPos).insert(new_x * boardSize + (new_y - 1));
			else {
				if (new_y - 2 >= 0) {
					if ((cells[new_x][new_y - 2] == CellType_Empty))
						if (this->_availableMoves.at(oldPos).insert(new_x * boardSize + (new_y - 2)).second)
							AddPossibleMoves_(oldPos, new_x * boardSize + (new_y - 2), type);
				}
			}
		}
		// RIGHT
		if (new_y + 1 <= 7) {
			if ((cells[new_x][new_y + 1] == CellType_Empty))
				this->_availableMoves.at(oldPos).insert(new_x * boardSize + (new_y+1));
			else {
				if (new_y + 2 <= 7) {
					if ((cells[new_x][new_y+2] == CellType_Empty))
						if (this->_availableMoves.at(oldPos).insert(new_x * boardSize + (new_y + 2)).second)
							AddPossibleMoves_(oldPos, new_x * boardSize + (new_y + 2), type);
				}
			}
		}
	}
	else {
		if (new_x - 2 >= 0) {
			if ((cells[new_x - 2][new_y] == CellType_Empty) && (cells[new_x - 1][new_y] != CellType_Empty))
				if (this->_availableMoves.at(oldPos).insert((new_x - 2) * boardSize + (new_y)).second)
					AddPossibleMoves_(oldPos, (new_x - 2) * boardSize + new_y, type);
		}
		if (new_x + 2 <= 7) {
			if ((cells[new_x + 2][new_y] == CellType_Empty) && (cells[new_x + 1][new_y] != CellType_Empty))
				if (this->_availableMoves.at(oldPos).insert((new_x + 2) * boardSize + (new_y)).second)
					AddPossibleMoves_(oldPos, (new_x + 2) * boardSize + new_y, type);
		}
		if (new_y - 2 >= 0) {
			if ((cells[new_x][new_y - 2] == CellType_Empty) && (cells[new_x][new_y - 1] != CellType_Empty))
				if (this->_availableMoves.at(oldPos).insert(new_x * boardSize + (new_y - 2)).second)
					AddPossibleMoves_(oldPos, new_x * boardSize + (new_y - 2), type);
		}
		if (new_y + 2 <= 7) {
			if ((cells[new_x][new_y + 2] == CellType_Empty) && (cells[new_x][new_y + 1] != CellType_Empty))
				if (this->_availableMoves.at(oldPos).insert(new_x * boardSize + (new_y + 2)).second)
					AddPossibleMoves_(oldPos, new_x * boardSize + (new_y + 2), type);
		}
	}
	delete tempBoard;
}

void CornersBoard::UpdateAvailableMoves_(CellType playerType, CellType opponentType)
{
	for (unsigned int i = 0; i < boardSize; ++i) {
		for (unsigned int j = 0; j < boardSize; ++j) {
			if (cells[i][j] == playerType) _availableMoves[i*boardSize + j];
		}
	}
	for (auto i = _availableMoves.begin(); i != _availableMoves.end(); ++i) {
		AddPossibleMoves_(i->first, i->first, playerType);
	}
}

bool CornersBoard::SetCell_(int start_row, int start_col, int end_row, int end_col, CellType type)
{
	if ((start_row == end_row) && (start_col == end_col)) return true;
	if (cells[start_row][start_col] != type && cells[end_row][end_col] == CellType_Empty) return false;
	cells[start_row][start_col] = CellType_Empty;
	cells[end_row][end_col] = type;
	return true;
}

bool CornersBoard::IsGameFinished_()
{
	int whiteCellInCity = 0;
	int blackCellInCity = 0;
	
	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int j = 0; j < 4; ++j) {
			if (cells[i][j] == CellType_W) whiteCellInCity++;
		}
	}
	for (unsigned int i = 5; i < boardSize; ++i) {
		for (unsigned int j = 4; j < boardSize; ++j) {
			if (cells[i][j] == CellType_B) blackCellInCity++;
		}
	}

	if (whiteCellInCity == 12) {
		_bGameFinished = true;
		this->_winner = 2;
		return true;
	}
	if (blackCellInCity == 12) {
		_bGameFinished = true;
		this->_winner = 1;
		return true;
	}
	
	// превышение количества ходов
	if (_currentTurn > this->_maxTurns) {
		if (whiteCellInCity == blackCellInCity) {
			_bGameFinished = true;
			this->_winner = 0;
			return true;
		}
		if (whiteCellInCity > blackCellInCity) {
			_bGameFinished = true;
			this->_winner = 2;
			return true;
		}
		if (whiteCellInCity < blackCellInCity) {
			_bGameFinished = true;
			this->_winner = 1;
			return true;
		}
	}
	return false;
}

CornersBoard::CornersBoard(unsigned int maxTurns)
{
	this->boardSize = 8;
	this->_bGameFinished = false;
	this->_winner = 0;
	this->_currentTurn = 0;
	this->_maxTurns = maxTurns;
	cells = new CellType*[boardSize];
	for (unsigned int i = 0; i < boardSize; ++i) {
		cells[i] = new CellType[boardSize];
	}
	for (unsigned int i = 0; i < boardSize; ++i) {
		for (unsigned int j = 0; j < boardSize; ++j) {
			if (i < 3 && j < 4) {
				cells[i][j] = CellType_B;
				continue;
			}
			if (i > 4 && j > 3) {
				cells[i][j] = CellType_W;
				continue;
			}
			cells[i][j] = CellType_Empty;
		}
	}

}

CornersBoard::CornersBoard(CornersBoard * board)
{
	this->boardSize = 8;
	this->_bGameFinished = board->_bGameFinished;
	this->_winner = board->_winner;
	this->_currentTurn = board->_currentTurn;
	this->_maxTurns = board->_maxTurns;
	cells = new CellType*[this->boardSize];
	for (unsigned int i = 0; i < this->boardSize; ++i)
		cells[i] = new CellType[this->boardSize];
	for (unsigned int i = 0; i < this->boardSize; ++i)
		for (unsigned int j = 0; j < boardSize; ++j)
			cells[i][j] = board->cells[i][j];
}

void CornersBoard::Show()
{
	for (unsigned int i = 0; i < boardSize + 1; ++i) {
		for (unsigned int j = 0; j < boardSize + 1; ++j) {
			if (i == 0 && j == 0) {
				std::cout << "%";
			}
			if (i == 0 && j != 0) {
				std::cout << j - 1;
			}
			if (i != 0 && j == 0) {
				std::cout << i - 1;
			}
			if (i != 0 && j != 0) {
				switch (cells[i - 1][j - 1])
				{
				case CellType_Empty:
					std::cout << "-";
					break;
				case CellType_W:
					std::cout << "W";
					break;
				case CellType_B:
					std::cout << "B";
					break;
				}
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

bool CornersBoard::SetCell(int start_row, int start_col, int end_row, int end_col, CellType type)
{
	std::unordered_map<int, std::unordered_set<int>>::const_iterator got = _availableMoves.find((start_row*boardSize + start_col));
	if (got == _availableMoves.end()) {
		return false;
	}
	else {
		std::unordered_set<int>::const_iterator gotPossibleMove = got->second.find(end_row*boardSize + end_col);
		if (gotPossibleMove == got->second.end()) {
			return false;
		}
		cells[start_row][start_col] = CellType_Empty;
		cells[end_row][end_col] = type;
		_currentTurn++;
		return true;
	}
}


bool CornersBoard::SetAvailableMoves(CellType type)
{
	_availableMoves.clear();
	CellType playerType = type;
	CellType opponentType;
	if (playerType == CellType_B) {
		opponentType = CellType_W;
	}
	else {
		opponentType = CellType_B;
	}

	UpdateAvailableMoves_(playerType, opponentType);

	if (_availableMoves.size() > 0) {
		return true;
	}
	else {
		return false;
	}

	return false;
}

unsigned int CornersBoard::GetCurrentTurn()
{
	return this->_currentTurn;
}

bool CornersBoard::CheckEndCondition()
{
	if (IsGameFinished_()) {
		return true;
	}
	return false;
}

int CornersBoard::GetWinner()
{
	return this->_winner;
}

CornersBoard::~CornersBoard()
{
	for (unsigned int i = 0; i < this->boardSize; ++i) {
		delete[] cells[i];
	}
	delete[] cells;
}
