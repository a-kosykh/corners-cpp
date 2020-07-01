#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "CellType.h"
class CornersBoard
{
private:
	unsigned int boardSize = 8;
	CellType** cells;
	std::unordered_map<int, std::unordered_set<int>> _availableMoves;
	void AddPossibleMoves_(int oldPos, int newPos, CellType type);
	void UpdateAvailableMoves_(CellType playerType, CellType opponentType);
	bool SetCell_(int start_row, int start_col,
		int end_row, int end_col, CellType type);
	unsigned int _maxTurns;
	unsigned int _currentTurn;

	bool IsGameFinished_();
	bool _bGameFinished;
	int _winner;

public:
	CornersBoard(unsigned int maxTurns);
	CornersBoard(CornersBoard* board);
	bool isGameFinished = false;
	void Show();
	bool SetCell(int start_row, int start_col,
		int end_row, int end_col, CellType type);
	bool SetAvailableMoves(CellType type);
	unsigned int GetCurrentTurn();
	bool CheckEndCondition();
	int GetWinner();
	virtual ~CornersBoard();
};

