/*
	File: GUI.h
	Author: Kaine Schultz

	Description: This file contains the user interface with which
	the user will select:
		-an image file 
		-the method that picture will be sorted into a color spectrum

*/

#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using std::string;
using sf::RectangleShape;
using sf::RenderWindow;
using sf::Text;


class GUI
{
public:
	GUI();
	~GUI();

	RectangleShape CreateButton(int CoordX, int CoordY);
	Text ButtonText(string buttonWriting, RectangleShape whichButton);
};