#include "Interface.h"
#include "common.h"
#include "Logger.h"


Interface::Interface(void)
{
	init();
	run();
}

sf::Vector2u Interface::windowSize;

Interface::~Interface(void)
{
}

void Interface::init()
{
	LINFO("Initiating interface");
	done = false;
	sf::VideoMode Mode(WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
	win.create(Mode,GAME_NAME);
	windowSize = win.getSize();
	menu = new MenuSystem();
	//Drawables::loadSprites();
}

void Interface::run()
{
	LINFO("Entering interface loop");
	sf::Event e;
	while(!done)
	{
		while(win.pollEvent(e))
		{
			switch(e.type)
			{
			case sf::Event::Closed:
				LINFO("Clicked close");
				done = true;
				break;
			case sf::Event::Resized:
				{
					LINFO("Resized window");
					sf::Vector2f size = static_cast<sf::Vector2f>(win.getSize());

					// Minimum size
					if(size.x < (float)WINDOW_MIN_WIDTH)
					{
						LWARN("Window width too small, reverting to minimum");
						size.x = WINDOW_MIN_WIDTH;
					}
					if(size.y < (float)WINDOW_MIN_HEIGHT)
					{
						size.y = WINDOW_MIN_HEIGHT;
						LWARN("Window height too small, reverting to minimum");
					}

					win.setSize(static_cast<sf::Vector2u>(size));
					win.setView(sf::View(sf::FloatRect(0.f, 0.f, size.x, size.y)));
					windowSize = win.getSize(); //update 
					break;
				}
			case sf::Event::KeyPressed:
				LINFO("Presssed key");
				//menu->processEvent(e);
				break;
			case sf::Event::MouseButtonPressed:
				LINFO("Clicked window");
				//menu->processEvent(e);
				break;
			}
		}
		win.clear();
		win.draw(*menu);
		win.display();
		sf::sleep(sf::milliseconds(5)); // in case vsync isn't supported, to avoid 100% CPU usage;
		                                //this may need to be removed if the game is expensive to run
	}
	LINFO("Interface loop done");
}