#include "Board.h"
#include "Tile.h"
#include "TextureManager.h"
#include <iostream>

#include <SFML/Graphics.hpp>

int main() {
	sf::Sprite spriteOne ;
	sf::Sprite spriteTwo;
	sf::Sprite spriteThree;
	sf::Sprite smileyFace;
	sf::Sprite test1;
	sf::Sprite test2;
	sf::Sprite test3;
	sf::Sprite spriteDebug;
	sf::Sprite scoreCounter;

    cout << "Minesweeper Game Starting..." << endl;
    sf::RenderWindow display(sf::VideoMode(800, 600), "Minesweeper Game - Gator Edition 2022",sf::Style::Close | sf::Style::Titlebar);
    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(sf::Color(200, 200, 200));
	Board board("config");

	spriteDebug.setTexture(TextureManager::GetTexture("debug"));
    spriteDebug.setPosition(500, 512);
    test1.setTexture(TextureManager::GetTexture("test_1"));
    test1.setPosition(564, 512);

    test2.setTexture(TextureManager::GetTexture("test_2"));
    test2.setPosition(628, 512);
	test3.setTexture(TextureManager::GetTexture("test_3"));
	test3.setPosition(692, 512);


	smileyFace.setTexture(TextureManager::GetTexture("face_happy"));
	smileyFace.setPosition(350, 512);
	spriteThree.setPosition(63, board.rows * 32);
	spriteTwo.setPosition(42, board.rows * 32);
	spriteOne.setPosition(21, board.rows* 32);
	scoreCounter.setPosition(0, board.rows * 32);
	bool debugging = false;


	while (display.isOpen()) {
		sf::Event ev;

		while (display.pollEvent(ev)) {
			bool left;
			if (ev.type == sf::Event::Closed) {
				display.close();
			}
			if (ev.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mPos = display.mapPixelToCoords(sf::Mouse::getPosition(display));
				if (ev.mouseButton.button == sf::Mouse::Left) {
                    board.LeftClick(mPos);
					if (spriteDebug.getGlobalBounds().contains(mPos)) {
						if (debugging) {
							debugging = false;
						}else {
							debugging = true;
						}	
					}
					if (test3.getGlobalBounds().contains(mPos)) {
                        board.TestBoard("testboard3");
					}
					if (smileyFace.getGlobalBounds().contains(mPos)) {
                        board.ConfigureBoard("config");
					}
					if (test1.getGlobalBounds().contains(mPos)) {
                        board.TestBoard("testboard1");
					}
					if (test2.getGlobalBounds().contains(mPos)) {
                        board.TestBoard("testboard2");
					}
				}
				if (ev.mouseButton.button == sf::Mouse::Right){
                    board.RightClick(mPos);
				}
			}
		}
		display.clear();
		for (int x = 0; x < board.columns; x+= 1){
			for (int y = 0; y < board.rows; y+= 1){
				board.TileLoc[x][y].Draw(display);
			}
		}
		if (debugging){
            board.DebugBoard(display);
		}

		switch (board.smileyFace) {
			case 1:
				smileyFace.setTexture(TextureManager::GetTexture("face_win"));
				break;
			case 2:
				smileyFace.setTexture(TextureManager::GetTexture("face_lose"));
				break;
			default:
				smileyFace.setTexture(TextureManager::GetTexture("face_happy"));
				break;
		}

		if (board.mineCount > 0) {
			scoreCounter.setTextureRect(sf::IntRect(0, 0, 0, 32));
		} else {
			scoreCounter.setTexture(TextureManager::GetTexture("digits"));
			scoreCounter.setTextureRect(sf::IntRect(210, 0, 21, 32));
		}

		for (int x = 0; x < 10; x+= 1) {
			int c = board.mineCount; //counter
			if (board.mineCount < 0)
				c = c * -1;

			if (c % 10 == x) {

				spriteThree.setTexture(TextureManager::GetTexture("digits"));
				spriteThree.setTextureRect(sf::IntRect(x * 21, 0, 21, 32));
			}
			if (c % 100 / 10 == x) {
				spriteTwo.setTexture(TextureManager::GetTexture("digits"));
				spriteTwo.setTextureRect(sf::IntRect(x * 21, 0, 21, 32));
			}
			if (c % 1000 / 100 == x) {
				spriteOne.setTexture(TextureManager::GetTexture("digits"));
				spriteOne.setTextureRect(sf::IntRect(x * 21, 0, 21, 32));
			}
		}

		display.draw(spriteOne);
		display.draw(spriteTwo);
		display.draw(spriteThree);
		display.draw(test1);
		display.draw(test2);
		display.draw(test3);
		display.draw(smileyFace);
		display.draw(spriteDebug);
		display.draw(scoreCounter);
		display.display();
	}

    TextureManager::Clear();

	return 0;
}