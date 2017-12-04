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


private:

};