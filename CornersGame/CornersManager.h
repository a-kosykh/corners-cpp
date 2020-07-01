#pragma once
#include "CornersBoard.h"
#include "CornersPlayer.h"
class CornersManager
{
	CornersBoard* board;
	CornersPlayer* player1;
	CornersPlayer* player2;
	CornersPlayer* currentPlayer;
	bool _isGameFinished = false;
public:
	CornersManager();
	virtual ~CornersManager();
	bool Start();
	void ShowBoard();
	void MakeMove();
	bool isGameFinished();
};

