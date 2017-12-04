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
	
	Image background;
	sf::Sprite BGSprite;
	sf::Texture BGTexture;
	BGTexture.create(window.getSize().x, window.getSize().y);
	BGSprite.setTexture(BGTexture);

	sf::Texture btnTexture;
	if (!btnTexture.loadFromFile("buttons.png"))
		cout << "Hub button texture did not load" << endl;

	//creates buttons for each photo the user can choose
	Button BtnSunset(btnTexture, "Sunset", sf::Vector2f(100, 548)),
		BtnEclipse(btnTexture, "Eclipse", sf::Vector2f(400, 548)),
		BtnWater(btnTexture, "Water", sf::Vector2f(700, 548));

	BtnSunset.renderBtn(window);
	BtnEclipse.renderBtn(window);
	BtnWater.renderBtn(window);
	window.draw(BGSprite);
	window.display();

	//for scaling image to fit current window
	float scaleX, scaleY;

	bool uploadFinished = false;
	while (uploadFinished == false)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				{
					if (BtnSunset.isClicked(sf::Mouse::getPosition(window)) == true)
					{}
					else if (BtnEclipse.isClicked(sf::Mouse::getPosition(window)) == true)
					{}
					else if (BtnWater.isClicked(sf::Mouse::getPosition(window)) == true)
					{}
					break;
				}
			case sf::Event::MouseButtonReleased:
				{
					if (BtnSunset.clickRelease(sf::Mouse::getPosition(window)) == true)
					{ 
						background.loadFromFile("sunset.jpg");
						BGTexture.loadFromImage(background);
						BGSprite.setTexture(BGTexture,true);

						scaleX = window.getSize().x / BGTexture.getSize().x;
						scaleY = window.getSize().y / BGTexture.getSize().y;

						BGSprite.scale(scaleX, scaleY);
					}
					else if (BtnEclipse.clickRelease(sf::Mouse::getPosition(window)) == true)
					{

						BGTexture.loadFromFile("Eclipse.jpg");
						BGSprite.setTexture(BGTexture);
					}
					else if (BtnWater.clickRelease(sf::Mouse::getPosition(window)) == true)
					{

						BGTexture.loadFromFile("water.jpg");
						BGSprite.setTexture(BGTexture);
					}
					break;
				}
			}//end switch

			window.clear();
			BtnSunset.renderBtn(window);
			BtnEclipse.renderBtn(window);
			BtnWater.renderBtn(window);
			window.draw(BGSprite);
			window.display();
		}

	}//end upload
}

