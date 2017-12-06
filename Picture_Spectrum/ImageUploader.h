/*
	File: ImageUploader.h
	Author:Kaine Schultz

	Description: This file is intended to contain methods which
	allow a user to select an image file for modification and 
	create a color spectrum of that image 

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

	

	//Mohammed's Code
	/* 
	void swap(int* a, int* b);
	void QuickSort(sf::Color *arr, int *HighColor, int *secondColor);
	sf::Color *pixelLine(sf::Color *arr, int *HighColor, int *secondColor);
	*/
};