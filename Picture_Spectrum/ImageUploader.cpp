#include "ImageUploader.h"



//empty constructor
ImageUploader::ImageUploader()
{}

//empty destructor
ImageUploader::~ImageUploader()
{}


/*
	Changes the window for previewing and selecting an image
*/
void ImageUploader::UploadHub(sf::RenderWindow &window)
{
	//black background
	window.clear(sf::Color(0, 0, 0));
	

	sf::Sprite BGSunset, BGEclipse, BGWater;
	sf::Texture BGTxSun,BGTxEcl, BGTxWat;
	sf::Sprite *CurBG = &BGSunset;

	//Pre-load the images
	if (!BGTxSun.loadFromFile("flowers.jpg"))
		cout << "sunset not loaded";
	if (!BGTxEcl.loadFromFile("Eclipse.jpg"))
		cout << "eclipse not loaded";
	if (!BGTxWat.loadFromFile("water.jpg"))
		cout << "water not loaded";
	
	float sunScaleX, sunScaleY,watScaleX, watScaleY;

	//get the inverse of the scale to show a preview
	//of the picture on the current window
	sunScaleX = (float) (window.getSize().x / BGTxSun.getSize().x);
	sunScaleY = (float) (window.getSize().y / BGTxSun.getSize().y);

	watScaleX = (float) (window.getSize().x / BGTxWat.getSize().x);
	watScaleY = (float) (window.getSize().y / BGTxWat.getSize().y);

	//load the textures to the sprites
	BGSunset.setTexture(BGTxSun);
	BGEclipse.setTexture(BGTxEcl);
	BGWater.setTexture(BGTxWat);

	//scale the sprites
	//BGSunset.scale(sunScaleX, sunScaleY);
	BGWater.scale(watScaleX,  watScaleY);


	//image selection buttons
	sf::Texture btnTexture;
	if (!btnTexture.loadFromFile("buttons.png"))
		cout << "Hub button texture did not load" << endl;

	//creates buttons for each photo the user can choose
	Button BtnSunset(btnTexture, "Flowers", sf::Vector2f(80, 548)),
		BtnEclipse(btnTexture, "Eclipse", sf::Vector2f(380, 548)),
		BtnWater(btnTexture, "Water", sf::Vector2f(680, 548)),
		BtnAccept(btnTexture,"Accept", sf::Vector2f(380, 648));

	//Title text
	sf::Text uploadText;
	sf::Font font;
	font.loadFromFile("steelfish-rg.ttf");
	uploadText.setFont(font);
	uploadText.setString("Choose a picture to modify");
	
	//center text
	sf::FloatRect textRec = uploadText.getLocalBounds();
	uploadText.setOrigin(textRec.width / 2, textRec.height / 2);
	uploadText.setPosition(window.getSize().x / 2, (window.getSize().y / 2) - 200);


	BtnSunset.renderBtn(window);
	BtnEclipse.renderBtn(window);
	BtnWater.renderBtn(window);
	BtnAccept.renderBtn(window);
	window.draw(*CurBG);//sunset background by default
	window.display();

	int pictureChoice = 1;//sunset by default
	bool uploadFinished = false;
	while (uploadFinished == false)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				return;
			}

			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				{
					if (BtnSunset.isClicked(sf::Mouse::getPosition(window)) == true)
					{
						pictureChoice = 1;
					}
					else if (BtnEclipse.isClicked(sf::Mouse::getPosition(window)) == true)
					{
						pictureChoice = 2;
					}
					else if (BtnWater.isClicked(sf::Mouse::getPosition(window)) == true)
					{
						pictureChoice = 3;
					}
					else if(BtnAccept.isClicked(sf::Mouse::getPosition(window)) == true)
					{}
					break;
				}
			case sf::Event::MouseButtonReleased:
				{
					if (BtnSunset.clickRelease(sf::Mouse::getPosition(window)) == true)
					{ 
						CurBG = &BGSunset;
					}
					else if (BtnEclipse.clickRelease(sf::Mouse::getPosition(window)) == true)
					{
						CurBG = &BGEclipse;
					}
					else if (BtnWater.clickRelease(sf::Mouse::getPosition(window)) == true)
					{
						CurBG = &BGWater;
					}
					else if (BtnAccept.clickRelease(sf::Mouse::getPosition(window)) == true)
					{
						RadixSpectrum(pictureChoice);
					}
					break;
				}
			}//end switch

			window.clear();
			window.draw(*CurBG); 
			BtnSunset.renderBtn(window);
			BtnEclipse.renderBtn(window);
			BtnWater.renderBtn(window);
			BtnAccept.renderBtn(window);
			window.draw(uploadText);
			window.display();
		}

	}//end upload
}



/*
	This method creates its own window the size of an image, and sorts the pixels
	of that image into a color spectrum.
*/
void ImageUploader::RadixSpectrum(int picChoice)
{
	Image modifyImage;
	switch (picChoice) {
	case 1://sunset
		modifyImage.loadFromFile("flowers.jpg");
		break;
	case 2://eclipse
		modifyImage.loadFromFile("Eclipse.jpg");
		break;
	case 3://water
		modifyImage.loadFromFile("water.jpg");
		break;
	default:
		cout << "Not a valid choice";
	}
	
	//establishes a window the same size as the image
	sf::RenderWindow RadixWindow(sf::VideoMode(modifyImage.getSize().x, modifyImage.getSize().y), "Radix Spectrum", sf::Style::Default);

	//create a 1D array of Pixels for the picture
	sf::Color *pixels = new sf::Color[modifyImage.getSize().x * modifyImage.getSize().y];	
	int pixelCounter = 0;
	for (int dexX = 0; dexX < modifyImage.getSize().x; dexX++)
	{
		for (int dexY = 0; dexY < modifyImage.getSize().y; dexY++)
		{
			pixels[pixelCounter++] = modifyImage.getPixel(dexX, dexY);
		}
	}

	sf::Texture imgTexture;
	imgTexture.loadFromImage(modifyImage);
	sf::Sprite imgSprite;
	imgSprite.setTexture(imgTexture);
	RadixWindow.draw(imgSprite);
	RadixWindow.display();

	//sort by brightness, low to high
	pixels = sortBrightness(pixels, (modifyImage.getSize().x * modifyImage.getSize().y));

	//sort each line by color
	pixels = sortColor(pixels, modifyImage.getSize().x, modifyImage.getSize().y);

	sf::Uint8 *modifiedPixels = new sf::Uint8[modifyImage.getSize().x * modifyImage.getSize().y * 4];
	
	int pxDex = 0;
	//convert the sf::Color array of pixels to sf::Uint8 to fit in an image
	for (int dex = 0; dex < modifyImage.getSize().x * modifyImage.getSize().y * 4; dex++)
	{
		modifiedPixels[dex++] = pixels[pxDex].r;
		modifiedPixels[dex++] = pixels[pxDex].g;
		modifiedPixels[dex++] = pixels[pxDex].b;
		modifiedPixels[dex] = pixels[pxDex].a;
		pxDex++;
	}

	sf::Image newImage;
	newImage.create(modifyImage.getSize().x, modifyImage.getSize().y,modifiedPixels);

	imgTexture.loadFromImage(newImage);
	imgSprite.setTexture(imgTexture);

	RadixWindow.draw(imgSprite);
	RadixWindow.display();
	
	while (RadixWindow.isOpen())
	{
		sf::Event event;
		while (RadixWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				RadixWindow.close();
			}
		}
	}

	//free pixel color data
	delete (pixels);
}



/*
	sorts all pixels by their brightness
*/
sf::Color * ImageUploader::sortBrightness(sf::Color *pixelArr,  int numElements)
{
	//numItems counts the number of elements with the 'i'th 
	//number in that digit place (ones place, tens, etc) 
	int digit, numItems[10] = { 0,0,0,0,0,0,0,0,0,0 }, Dex = 0;

	sf::Color *outputArr = new sf::Color[numElements];
	
	for (digit = 1; digit <= 100; digit *= 10)
	{
	//resets numItems element values
		for (Dex = 0; Dex < 10;Dex++)
		{
			numItems[Dex] = 0;
		}
	
	//how many elements of each number in current digit
		for (Dex = 0; Dex < numElements; Dex++)
		{
			//total sum of pixel elements over the digit % 10
			numItems[((pixelArr[Dex].r + pixelArr[Dex].g + pixelArr[Dex].b) / digit) % 10]++;
		}

	//cumulative addition 
		for (Dex = 1; Dex < 10; Dex++)
		{
			numItems[Dex] += numItems[Dex - 1];
		}

	//based on brightness, places the pixels in order in a temporary 'outputArr'
		for (Dex = numElements - 1; Dex >= 0; Dex--)
		{
			outputArr[numItems[((pixelArr[Dex].r + pixelArr[Dex].g + pixelArr[Dex].b) / digit) % 10] - 1] = pixelArr[Dex];
			numItems[((pixelArr[Dex].r + pixelArr[Dex].g + pixelArr[Dex].b) / digit) % 10]--;
		}

	//copies the new order of the pixels to the original array
	//	for (Dex = 0; Dex < numElements; Dex++)
		//{
		//	pixelArr[Dex] = outputArr[Dex];
		//}
	}

	//delete (outputArr);

	return outputArr;
}



/*
	Sorts each line of pixels by color:
	- breaks the array into lines
	- breaks each line into 6 sub-arrays
	- calls RadixLine to sort each sub-array
	- recombines the lines into one array
*/
sf::Color *ImageUploader::sortColor(sf::Color *pixelArr, int sizeX, int sizeY)
{
	sf::Color *outputArr = new sf::Color[sizeX * sizeY];
	sf::Color *oneLine = new sf::Color[sizeX];


	int dex = 0, rgCount = 0,grCount = 0, gbCount = 0, 
		bgCount = 0, brCount = 0, rbCount = 0, i = 0;
	
	//create int arrays of each sub-array's top two color values
	int rgR[900], rgG[900],
		grR[900], grG[900],
		rbR[900], rbB[900],
		brR[900], brB[900],
		gbG[900], gbB[900],
		bgG[900], bgB[900];


	//traverse each line of the picture
	for (int lineDex = 0; lineDex < sizeY; lineDex++) {



		//sub-arrays: contain pixels with higest value and second 
		//highest value. rgArr has red with the highest val and 
		//green with the second highest val. 
		sf::Color *rgArr = new sf::Color[sizeX];
		sf::Color *grArr = new sf::Color[sizeX];
		sf::Color *gbArr = new sf::Color[sizeX];
		sf::Color *bgArr = new sf::Color[sizeX];
		sf::Color *brArr = new sf::Color[sizeX];
		sf::Color *rbArr = new sf::Color[sizeX];



		rgCount = 0, grCount = 0, gbCount = 0,
			bgCount = 0, brCount = 0, rbCount = 0, i = 0;

		//looks at one line of the picture
		for (i = 0; i < sizeX; i++)
		{
			oneLine[i] = pixelArr[(lineDex * sizeX) + i];
		}

		//places oneLine pixels into appropriate sub array
		for (dex = 0; dex < sizeX; dex++)
		{
			//red largest
			if (oneLine[dex].r > oneLine[dex].g &&
				oneLine[dex].r > oneLine[dex].b ||
				oneLine[dex].r == oneLine[dex].g &&
				oneLine[dex].r == oneLine[dex].b)
			{
				if (oneLine[dex].g > oneLine[dex].b)
				{
					rgArr[rgCount++] = oneLine[dex];
				}
				else {
					rbArr[rbCount++] = oneLine[dex];
				}
			}
			//green largest
			else if (oneLine[dex].g > oneLine[dex].r &&
				oneLine[dex].g > oneLine[dex].b ||
				oneLine[dex].g == oneLine[dex].r &&
				oneLine[dex].g > oneLine[dex].b)
			{
				if (oneLine[dex].r > oneLine[dex].b)
				{
					grArr[grCount++] = oneLine[dex];
				}
				else {
					gbArr[gbCount++] == oneLine[dex];
				}
			}
			//blue largest
			else if (oneLine[dex].b > oneLine[dex].r &&
				oneLine[dex].b > oneLine[dex].g ||
				oneLine[dex].b == oneLine[dex].g &&
				oneLine[dex].b > oneLine[dex].r ||
				oneLine[dex].b == oneLine[dex].r &&
				oneLine[dex].b > oneLine[dex].g)
			{
				if (oneLine[dex].r > oneLine[dex].g)
				{
					brArr[brCount++] = oneLine[dex];
				}
				else {
					bgArr[bgCount++] = oneLine[dex];
				}
			}
		}//end sorting into sub-arrays 


		for ( i = 0; i < rgCount; i++)
		{
			rgR[i] = rgArr[i].r;
			rgG[i] = rgArr[i].g;
		}
		for ( i = 0; i < grCount; i++)
		{
			grR[i] = grArr[i].r;
			grG[i] = grArr[i].g;
		}
		for ( i = 0; i < rbCount; i++)
		{
			rbR[i] = rbArr[i].r;
			rbB[i] = rbArr[i].b;
		}
		for (int i = 0; i < brCount; i++)
		{
			brR[i] = brArr[i].r;
			brB[i] = brArr[i].b;
		}
		for (int i = 0; i < gbCount; i++)
		{
			gbB[i] = gbArr[i].b;
			gbG[i] = gbArr[i].g;
		}
		for (int i = 0; i < bgCount; i++)
		{
			bgB[i] = bgArr[i].b;
			bgG[i] = bgArr[i].g;
		}


	//sort each sub-array
		if (rgCount > 0)
		{
			rgArr = RadixLine(rgArr, rgR, rgG, rgCount);
		}
		if (grCount > 0) {
			grArr = RadixLine(grArr, grG, grR, grCount);
		}
		if (gbCount > 0) {
			gbArr = RadixLine(gbArr, gbG, gbB, gbCount);
		}
		if (bgCount > 0) {
			bgArr = RadixLine(bgArr, bgB, bgG, bgCount);
		}
		if (brCount > 0) {
			brArr = RadixLine(brArr, brB, brR, brCount);
		}
		if (rbCount > 0) {
			rbArr = RadixLine(rbArr, rbR, rbB, rbCount);
		}


	//place sub-arrays back into 'oneLine'
		i = 0;
		for (dex = 0; dex < rgCount; dex++)
		{
			oneLine[dex] = rgArr[i++];
		}
		grCount += rgCount;
		i = 0;
		for (dex; dex < grCount; dex++)
		{
			oneLine[dex] = grArr[i++];
		}
		gbCount += grCount;
		i = 0;
		for (dex; dex < gbCount; dex++)
		{
			oneLine[dex] = gbArr[i++];
		}
		bgCount += gbCount;
		i = 0;
		for (dex; dex < bgCount; dex++)
		{
			oneLine[dex] = bgArr[i++];
		}
		brCount += bgCount;
		i = 0;
		for (dex; dex < brCount; dex++)
		{
			oneLine[dex] = brArr[i++];
		}
		rbCount += brCount;
		i = 0;
		for (dex; dex < rbCount; dex++)
		{
			oneLine[dex] = rbArr[i++];
		}

		
		//place oneLine into outputArr
		dex = 0;
		for (dex; dex < sizeX; dex++)
		{
			outputArr[(lineDex* sizeX) + dex] = oneLine[dex];
		}
	
		delete (rgArr);
		delete (rbArr);
		delete (grArr);
		delete (gbArr);
		delete (brArr);
		delete (bgArr);

}//final line sorted

	delete(oneLine);
	
	return outputArr;

}



/*
	Looks at one sf::Color subarray, organizes it by the difference between its 
	largest and 2nd largest color elements
*/
sf::Color *ImageUploader::RadixLine(sf::Color *arr, int *primaryColor, int *secondaryColor, int numElements)
{
	//numItems counts the number of elements with the 'i'th 
	//number in that digit place (ones place, tens, etc) 
	int digit, numItems[10], Dex = 0;

	sf::Color *outputArr = new sf::Color[numElements];

	for (digit = 1; digit <= 100; digit *= 10)
	{
		//resets numItems element values
		for (Dex = 0; Dex < 10; Dex++)
		{
			numItems[Dex] = 0;
		}

		//how many elements of each number in current digit
		for (Dex = 0; Dex < numElements; Dex++)
		{
			numItems[((primaryColor[Dex] - secondaryColor[Dex]) / digit) % 10]++;
		}

		//cumulative addition 
		for (Dex = 1; Dex < 10; Dex++)
		{
			numItems[Dex] += numItems[Dex - 1];
		}

		//based on brightness, places the pixels in order in a temporary 'outputArr'
		for (Dex = numElements - 1; Dex >= 0; Dex--)
		{
			outputArr[numItems[((primaryColor[Dex] - secondaryColor[Dex]) / digit) % 10] - 1] = arr[Dex];
			numItems[((primaryColor[Dex] - secondaryColor[Dex]) / digit) % 10]--;
		}

		//copies the new order of the pixels to the original array    
		for (Dex = 0; Dex < numElements; Dex++)
		{
			arr[Dex] = outputArr[Dex];
		}
	}

	//delete (outputArr);

	return outputArr;
}










//Mohammed's Code
/* 
sf::Color *ImageUploader::pixelLine(sf::Color *arr, int *HighColor, int *secondColor) {

	pivot = arr[HighColor];

	i = (secondColor - 1) // Index of smaller element

		for (j = secondColor; j &lt; = HighColor - 1; j++)
		{

			if (arr[j] & lt; = pivot)
			{
				i++;
				swap arr[i] and arr[j]
			}
		}
	swap arr[i + 1] and arr[HighColor])
	return (i + 1)
}


void ImageUploader::swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
void ImageUploader::QuickSort(sf::Color *arr, int *HighColor, int *secondColor)
{
	if (secondColor &lt; HighColor)
	{

		int pi = pixelLine(arr, secondColor, HighColor);


		// Separately sort elements before

		QuickSort(arr, secondColor, pi - 1);
		QuickSort(arr, pi + 1, HighColor);
	}
}
*/