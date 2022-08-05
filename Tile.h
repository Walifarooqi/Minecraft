#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>


using namespace std;

class Tile
{
	int xB;
	int yB;
	int num;
	bool bomb;
	bool isShown;
	bool marker;
	sf::Vector2f TilePosition;
	sf::Sprite CurrSprite;
	sf::Sprite FlagMarker;
	sf::Sprite SpriteNum;
public:
	vector<Tile*> touchingSquares;
	int GetMineCounts() const;
	bool Revealed();
	bool FlagPresent() const;
	bool MinePresent() const;
	bool SetFlag();
	void SetCountMine(int a);
	void SetReveal(bool bug);
	void SetMineHere();
	void SetSprite(string textureName);

	void Reveal();
	void Draw(sf::RenderWindow& window);
	sf::Sprite GetFlagSprite();
	sf::Sprite GetSpriteCount();
	sf::Sprite GetSprite();
	Tile(bool bomb, int xPos, int yPos);

};

