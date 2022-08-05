#include "Board.h"



void Board::ConfigureBoard(const string& title){
	smileyFace = 0;
	stop = false;
	board.clear();
	TileLoc.clear();
	mineCount = 0;

	columns = 0;
	rows     = 0;

	for (int x = 0; x < columns; x++){
		vector <Tile> r;
		for (int y = 0; y < rows    ; y++){
			r.emplace_back(false, x, y);
		}
		TileLoc.push_back(r);
	}
	string folder = "boards/";
	folder += title + ".cfg";
	ifstream file(folder);


	if (file.is_open()){
		string intData;
		getline(file, intData);
		columns = stoi(intData);
		getline(file, intData);
		rows     = stoi(intData);
		getline(file, intData);
		mineCount = stoi(intData);
	}

	for (int x = 0; x < columns; x++) {
		vector <Tile> rowVector;
		for (int y = 0; y < rows    ; y++) {
			rowVector.emplace_back(false, x, y);
		}
		TileLoc.push_back(rowVector);
	}

	int count = mineCount;
	while (count != 0){
		int randomX = rand() % (columns - 1) + 0;
		int randomY = rand() % (rows     - 1) + 0;

		if (!TileLoc[randomX][randomY].MinePresent()){
            TileLoc[randomX][randomY].SetMineHere();
			count--;
		}
	}

	for (int x = 0; x < columns; x++){
		for (int y = 0; y < rows    ; y++){
            NeighboringSquares(x, y);
		}
	}
}


void Board::TestBoard(const string& title){
	smileyFace = 0;
	stop = false;
	board.clear();
	TileLoc.clear();
	mineCount = 0;

	columns = 0;
	rows = 0;

	string path = "boards/";
	path += title + ".brd";
	ifstream file(path);

	// juicy
	int value;

	//row counter 
	int rowCounter = 0;
	int colCounter = 0;


	if (file.is_open()){
		string lineOfData;

		while (getline(file, lineOfData)){
			for (char x : lineOfData){
				int a = x - 48;
				board.push_back(a);
			}
			rowCounter++;
		}
		colCounter = lineOfData.size();
	}

	columns = rowCounter;
	rows     = colCounter;

	int count = 0;
	for (int x = 0; x < columns; x++){
		vector <Tile> r;
		for (int y = 0; y < rows    ; y++){
			bool mine = false;
			if (board.at(count) == 1){
				mine = true;
				mineCount++;
			}
			r.push_back(Tile(mine, y, x));
			count++;
		}
		TileLoc.push_back(r);
	}

	for (int x = 0; x < columns; x++){
		for (int y = 0; y < rows    ; y++){
            NeighboringSquares(x, y);
		}
	}
}

void Board::NeighboringSquares(int xPos, int yPos){
	int counter = -1;
	if ((xPos != TileLoc.size() - 1 && xPos != 0) && (yPos != TileLoc[xPos].size() - 1 && yPos != 0)){
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos][yPos - 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos][yPos + 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos + 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos - 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos + 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos - 1]);


		for (auto & touchingSquare : TileLoc[xPos][yPos].touchingSquares){
			if (touchingSquare->MinePresent()) {
				counter++;
			}
		}
	}
	else if (xPos == 0 && yPos == 0){
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos][yPos + 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos + 1]);


		for (auto & touchingSquare : TileLoc[xPos][yPos].touchingSquares){
			if (touchingSquare->MinePresent()) {
				counter++;
			}
		}
	}
	else if (xPos == 0 && yPos == TileLoc[xPos].size() - 1){
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos][yPos - 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos - 1]);

		for (auto & touchingSquare : TileLoc[xPos][yPos].touchingSquares){
			if (touchingSquare->MinePresent()){
				counter++;
			}
		}
	}
	else if (yPos == 0 && xPos == TileLoc.size() - 1){
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos][yPos + 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos + 1]);
		for (auto & touchingSquare : TileLoc[xPos][yPos].touchingSquares){
			if (touchingSquare->MinePresent()) {
				counter++;
			}
		}
	} else if (xPos == TileLoc.size() - 1 && yPos == TileLoc[xPos].size() - 1){
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos][yPos - 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos - 1]);
		for (auto & touchingSquare : TileLoc[xPos][yPos].touchingSquares){
			if (touchingSquare->MinePresent())
				counter++;
		}
	} else if (xPos == 0) {
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos - 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos + 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos][yPos + 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos][yPos - 1]);

		for (auto & touchingSquare : TileLoc[xPos][yPos].touchingSquares){
			if (touchingSquare->MinePresent())
				counter++;
		}
	} else if (yPos == 0) {
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos + 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos + 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos][yPos + 1]);


		for (auto & touchingSquare : TileLoc[xPos][yPos].touchingSquares){
			if (touchingSquare->MinePresent())
				counter++;
		}
	} else if (yPos == TileLoc[xPos].size() - 1){
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos][yPos - 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos + 1][yPos - 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos - 1]);

		for (auto & touchingSquare : TileLoc[xPos][yPos].touchingSquares){
			if (touchingSquare->MinePresent())
				counter++;
		}
	} else if (xPos == TileLoc.size() - 1) {
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos + 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos - 1][yPos - 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos][yPos + 1]);
		TileLoc[xPos][yPos].touchingSquares.push_back(&TileLoc[xPos][yPos - 1]);

		for (auto & touchingSquare : TileLoc[xPos][yPos].touchingSquares){
			if (touchingSquare->MinePresent())
				counter++;
		}
	}

	if (counter != -1){
		counter += 1;
	}

    TileLoc[xPos][yPos].SetCountMine(counter);
}


void Board::LeftClick(sf::Vector2f mPos){
	bool L = false;
	for (int x = 0; x < columns; x++){
		for (int y = 0; y < rows    ; y++){
			if (TileLoc[x][y].GetSprite().getGlobalBounds().contains(mPos) && !TileLoc[x][y].FlagPresent() &&
                TileLoc[x][y].MinePresent() && !stop) {
				L = true;
				stop = true;
			} else if (TileLoc[x][y].GetSprite().getGlobalBounds().contains(mPos)
                       && !TileLoc[x][y].FlagPresent() && !stop)
			{
                TileLoc[x][y].SetReveal(false);
                TileLoc[x][y].SetSprite("tile_revealed");
                TileLoc[x][y].Reveal();
			}

		}
	}
    WinCheck();
    LossCheck(L);
}

bool Board::WinCheck() {
	bool winning = false;
	int totalNotMineTiles = columns * rows   - mineCount;
	int c = 0;

	for (int x = 0; x < columns; x++){
		for (int y = 0; y < rows    ; y++){
			if (TileLoc[x][y].Revealed() || (TileLoc[x][y].FlagPresent() && TileLoc[x][y].MinePresent())){
				c += 1;
			}
		}
	}
	if (totalNotMineTiles == c){
		stop = true;
		smileyFace = 1;
		for (int x = 0; x < columns; x++){
			for (int y = 0; y < rows    ; y++){
				if (TileLoc[x][y].MinePresent() && !TileLoc[x][y].FlagPresent()){
                    TileLoc[x][y].SetReveal(false);
                    TileLoc[x][y].SetMineHere();
					mineCount--;
				}
			}
		}
	}
	return winning;
}


void Board::DebugBoard(sf::RenderWindow& display){
	for (int x = 0; x < columns; x++){
		for (int y = 0; y < rows    ; y++){
			if (TileLoc[x][y].MinePresent() && !stop){
				display.draw(TileLoc[x][y].GetSpriteCount());
			}
		}
	}
}

void Board::LossCheck(bool L) {
	if (L == true){
		smileyFace = 2;
		for (int x = 0; x < columns; x++){
			for (int y = 0; y < rows    ; y++){
				if (TileLoc[x][y].MinePresent()){
                    TileLoc[x][y].SetReveal(false);
                    TileLoc[x][y].SetSprite("tile_revealed");
				}
			}
		}
	}
}

Board::Board(const string& file){
	stop = false;
    ConfigureBoard(file);
}

void Board::RightClick(sf::Vector2f mPos) {
    for (int x = 0; x < columns; x++) {
        for (int y = 0; y < rows    ; y++) {
            if (TileLoc[x][y].GetSprite().getGlobalBounds().contains(mPos) && !TileLoc[x][y].Revealed()) {
                if (TileLoc[x][y].SetFlag()) {
                    mineCount -= 1;
                }
                else {
                    mineCount += 1;
                }
            }
        }
    }
}