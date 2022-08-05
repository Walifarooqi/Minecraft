#include "Tile.h"
#include "TextureManager.h"

void Tile::SetSprite(string textureName){
	CurrSprite.setTexture(TextureManager::GetTexture(textureName));
	CurrSprite.setPosition(TilePosition.x, TilePosition.y);
}

bool Tile::Revealed(){
	return isShown;
}

Tile::Tile(bool bomb, int xPos, int yPos){
	this->isShown = false;
	this->marker = false;
	this->num = -1;
	this->bomb = bomb;
    this->xB = xPos;
    this->yB = yPos;
    TilePosition.x = 32 * xPos;
    TilePosition.y = 32 * yPos;

	CurrSprite.setTexture(TextureManager::GetTexture("tile_hidden"));
	CurrSprite.setPosition(TilePosition);

}



sf::Sprite Tile::GetSprite(){
	return CurrSprite;
}

sf::Sprite Tile::GetFlagSprite(){
	FlagMarker.setTexture(TextureManager::GetTexture("flag"));
	FlagMarker.setPosition(TilePosition);

	return FlagMarker;
}

void Tile::SetMineHere(){
	bomb = true;
	SpriteNum.setTexture(TextureManager::GetTexture("mine"));
	SpriteNum.setPosition(TilePosition);
}

bool Tile::FlagPresent() const{
	return marker;
}

sf::Sprite Tile::GetSpriteCount(){
	if (!bomb){
		string textName = "number_";
		textName += to_string(num);
		SpriteNum.setTexture(TextureManager::GetTexture(textName));
		SpriteNum.setPosition(TilePosition);
	} else {
        SpriteNum.setTexture(TextureManager::GetTexture("mine"));
        SpriteNum.setPosition(TilePosition);
    }
	return SpriteNum;
}

void Tile::SetReveal(bool bug){
	if (!isShown){
		isShown = true;
	} else if (bug){
		isShown = false;
	}
}

void Tile::SetCountMine(int a){
	this->num = a;
}


int Tile::GetMineCounts() const{
	return num;
}

void Tile::Reveal(){
	for (int i = 0; touchingSquares.size() > i; i += 1){
		if (touchingSquares.at(i)->GetMineCounts() >= 0 && !touchingSquares.at(i)->MinePresent() && !touchingSquares.at(
                i)->FlagPresent()){
            touchingSquares.at(i)->SetReveal(false);
            touchingSquares.at(i)->SetSprite("tile_revealed");
		} else if (!touchingSquares.at(i)->Revealed() && touchingSquares.at(i)->GetMineCounts() == -1 && !touchingSquares.at(
                i)->Revealed() && !touchingSquares.at(i)->MinePresent()){
            touchingSquares.at(i)->SetReveal(false);
            touchingSquares.at(i)->SetSprite("tile_revealed");
            touchingSquares.at(i)->Reveal();
		}
	}
}


void Tile::Draw(sf::RenderWindow& window){
	if (FlagPresent()){
		window.draw(GetSprite());
		window.draw(GetFlagSprite());

	}else if (Revealed()){
		window.draw(GetSprite());
		if (num != -1 || MinePresent())
		{
			window.draw(GetSpriteCount());
		}
	}else {
		window.draw(GetSprite());
	}
}

bool Tile::MinePresent() const {
	return bomb;
}

bool Tile::SetFlag(){
	if (!marker){
		marker = true;
		return marker;
	} else {
		marker = false;
		return marker;
	}
}

