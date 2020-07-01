#pragma once
#include "CornersBoard.h"
#include <string>
class CornersPlayer
{
	CornersBoard *board;
	CellType cellType;
	std::string name;
public:
	CornersPlayer();
	virtual ~CornersPlayer();
	void SetupPlayer(std::string name, CellType ct);
	CellType GetType();
	void SetBoard(CornersBoard* board);
	bool MakeMove();
	std::string GetName();
};

