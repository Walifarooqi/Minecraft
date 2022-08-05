#pragma once
#include "Tile.h"
#include <vector>
#include <fstream>

class Board
{
private:
	vector<int> board;
public:
	int mineCount;
	int rows; // y rows
	int columns; // x columns
	int smileyFace = 0;
	bool stop;
	vector<vector<Tile>> TileLoc;
	void DebugBoard(sf::RenderWindow& display);
	void TestBoard(const string& title);
	void ConfigureBoard(const string& title);
	void RightClick(sf::Vector2f mPos);
	void LeftClick(sf::Vector2f mPos);
	void NeighboringSquares(int xPos, int yPos);
	void LossCheck(bool L);
	bool WinCheck();
	Board(const string& file);
};