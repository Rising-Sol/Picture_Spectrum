/*

*/

#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class Button 
{
public:
	Button(sf::Texture &texture, string text, sf::Vector2f location);

	bool isClicked(sf::Vector2i mousePosition);
	bool clickRelease(sf::Vector2i mousePosition);
	void renderBtn(sf::RenderWindow &window);
private:
	sf::Sprite SPnormal;
	sf::Sprite SPclicked;
	sf::Sprite *CurState;
	sf::Text btnText;
	sf::Font btnFont;
};