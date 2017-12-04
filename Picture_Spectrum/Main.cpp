#include <string>
#include "Button.h"
#include "ImageUploader.h"


int main()
{

	sf::RenderWindow mainWindow(sf::VideoMode(1024, 768), "Picture Spectrum", sf::Style::Default);
	sf::Texture BtnTexture;
	sf::Texture WndTexture;
	sf::Sprite background;
	sf::Text HomePage;
	sf::Font font;

	font.loadFromFile("steelfish-rg.ttf");
	
	//sync framerate with the monitor
	mainWindow.setVerticalSyncEnabled(true);
	mainWindow.clear(sf::Color(60,60,150));

	//load button and window textures
	if (!BtnTexture.loadFromFile("buttons.png"))
		std::cout <<"Button texture not loaded" << endl;
	if (!WndTexture.loadFromFile("buttons.png"))
		std::cout << "Window texture not loaded" << endl;

	//create two buttons 
	Button BtnSelectImage(BtnTexture, "Select an Image", sf::Vector2f(142, 548)),
		BtnExit(BtnTexture, "Exit", sf::Vector2f(630, 548));
	
	//scales a texture to fit the window
	float scaleX = (float) mainWindow.getSize().x / WndTexture.getSize().x;
	float scaleY = (float)mainWindow.getSize().y / (WndTexture.getSize().y / 2);

	WndTexture.setSmooth(true);
	background.setTexture(WndTexture);
	background.setTextureRect(sf::IntRect(0, 0, WndTexture.getSize().x, WndTexture.getSize().y / 2));
	background.setColor(sf::Color(0,0,0));
	background.setScale(scaleX, scaleY);

	//Homepage text
	HomePage.setFont(font);
	HomePage.setCharacterSize(35);
	string homeText;
	homeText = "\t\t\t\t\t\t\t\t\t\tWelcome to the Picture Spectrum application!\n\nThis program lets";
	homeText.append(" you upload a picture, and transform it into a");
	homeText.append(" color spectrum of its pixels.\n");
	homeText.append("\t\t\t\t\t\t\t\t\t\t\t\t\tClick a button below to begin.");
	HomePage.setString(homeText);

	//center text
	sf::FloatRect textRec = HomePage.getLocalBounds();
	HomePage.setOrigin(textRec.width / 2, textRec.height / 2);
	HomePage.setPosition(mainWindow.getSize().x / 2,( mainWindow.getSize().y / 2) - 40);

	//displays all menu pieces
	BtnSelectImage.renderBtn(mainWindow);
	BtnExit.renderBtn(mainWindow);
	mainWindow.draw(background);
	mainWindow.draw(HomePage);
	mainWindow.display();

	//runs the program while the window is open
	while (mainWindow.isOpen())
	{
		mainWindow.clear(sf::Color(60,60,150));
		//closes the window
		sf::Event event;
		while (mainWindow.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
			{
				mainWindow.close();
			}

			//user clicks on a button
			switch (event.type) {
			case sf::Event::MouseButtonPressed:
				//changes button to its clicked appearance
				if (BtnSelectImage.isClicked(sf::Mouse::getPosition(mainWindow)) == true)
				{}
				else if (BtnExit.isClicked(sf::Mouse::getPosition(mainWindow)) == true)
				{}
				break;

			//reverts button to normal state either way. Only does enclosed code if true
			case sf::Event::MouseButtonReleased:
				if (BtnSelectImage.clickRelease(sf::Mouse::getPosition(mainWindow)) == true)
				{
					BtnSelectImage.renderBtn(mainWindow);
					mainWindow.display();
					ImageUploader uploadWindow;
					uploadWindow.UploadHub(mainWindow);
					
				}
				else if (BtnExit.clickRelease(sf::Mouse::getPosition(mainWindow)) == true)
				{
					BtnExit.renderBtn(mainWindow);
					mainWindow.display();
					mainWindow.close();
				}
				break;
			}//endswitch
			
		}//endpoll
		BtnSelectImage.renderBtn(mainWindow);
		BtnExit.renderBtn(mainWindow);
		mainWindow.draw(background);
		mainWindow.draw(HomePage);
		mainWindow.display();
	}

	return 0;
}