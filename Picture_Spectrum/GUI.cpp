#include "GUI.h"


GUI::GUI()
{

}



GUI::~GUI()
{

}




/*
	Creates a rectangle at (x,y) input coordinates
*/
RectangleShape GUI::CreateButton(int CoordX, int CoordY)
{
	sf::RectangleShape ImageSelect(sf::Vector2f(200,50));
	ImageSelect.setPosition(sf::Vector2f(CoordX, CoordY));
	ImageSelect.setFillColor(sf::Color::White); 
	ImageSelect.setOutlineThickness(10);
	ImageSelect.setOutlineColor(sf::Color(128, 128, 128));

	return ImageSelect;
}


/*
	Writes a string onto the button provided
*/
Text GUI::ButtonText(string buttonWriting, RectangleShape whichButton)
{
	Text WriteOnButton;
	sf::Font font;

	if (font.loadFromFile("Tw Cen MT.ttf")) {
		WriteOnButton.setFont(font);
		WriteOnButton.setString(buttonWriting);
		WriteOnButton.setCharacterSize(20);
		WriteOnButton.setColor(sf::Color::White);
	}
	//whichButton.getPosition();
//	WriteOnButton.setPosition(sf::Vector2f(200, 300));

	return WriteOnButton;
}