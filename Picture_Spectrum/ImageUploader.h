/*
	File: ImageUploader.h
	Author:Kaine Schultz

	Description: This file is intended to contain methods which
	allow a user to select an image file for modification

*/

#pragma once

#include "Button.h"

class ImageUploader : public sf::Image
{
public:
	ImageUploader();
	~ImageUploader();

	void UploadHub(sf::RenderWindow &window);
	void RadixSpectrum(int picChoice);
	sf::Color *sortBrightness(sf::Color *pixelArr, int numElements);
	sf::Color *sortColor(sf::Color *pixelArr, int sizeX, int sizeY);
	sf::Color *RadixLine(sf::Color *arr, int *primaryColor, int *secondaryColor, int numElements);
};