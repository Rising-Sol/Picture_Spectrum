#include "Button.h"


/*
	Initializes a button with an input texture, a string to 
	label the button, and the button's intended position
*/
Button::Button(sf::Texture &texture, string text, sf::Vector2f location)
{
	SPnormal.setTexture(texture);
	SPnormal.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y / 2));
	SPnormal.setColor(sf::Color(0,100,255));
	SPnormal.setPosition(location.x,location.y);

	SPclicked.setTexture(texture);
	SPclicked.setTextureRect(sf::IntRect(0, texture.getSize().y / 2, texture.getSize().x, texture.getSize().y / 2));
	SPclicked.setPosition(location.x,location.y);

	CurState = &SPnormal;

	if (!btnFont.loadFromFile("steelfish-rg.ttf"))
		cout << "File not loaded" << endl;
	btnText.setFont(btnFont);
	btnText.setString(text);
	btnText.setPosition(location.x + (texture.getSize().x / 4), location.y + 15);
	btnText.setFillColor(sf::Color(250, 250, 250));

}



/*
	Checks if the mouse is above the button and left clicking
	and changes the current button state depending on the result
*/
bool Button::isClicked(sf::Vector2i mousePosition)
{
	bool truthiness = false;
	if (mousePosition.x >= SPnormal.getPosition().x &&
		mousePosition.x <= SPnormal.getPosition().x + 250)
	{
		if (mousePosition.y >= SPnormal.getPosition().y &&
			mousePosition.y <= SPnormal.getPosition().y + 150)
		{
			CurState = &SPclicked;
			truthiness = true;
		}
	}
	else 
	{
		truthiness = false;
		CurState = &SPnormal;
	}
	return truthiness;
}



/*
	reverts button back to normal state regardless of mouse
	position. Returns whether mouse was in position or not
	when released.
*/
bool Button::clickRelease(sf::Vector2i mousePosition)
{
	bool truthiness = false;
	if (mousePosition.x >= SPnormal.getPosition().x &&
		mousePosition.x <= SPnormal.getPosition().x + 250)
	{
		if (mousePosition.y >= SPnormal.getPosition().y &&
			mousePosition.y <= SPnormal.getPosition().y + 150)
		{
			CurState = &SPnormal;
			truthiness = true;
		}
	}
	else
	{
		truthiness = false;
		CurState = &SPnormal;
	}
	return truthiness;
}



/*
	Draws the button to the screen in its current state
	(clicked or normal)
*/
void Button::renderBtn(sf::RenderWindow &window)
{
	window.draw(*CurState);
	window.draw(btnText);
}