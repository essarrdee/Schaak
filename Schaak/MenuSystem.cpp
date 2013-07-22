#include "MenuSystem.h"
#include "Interface.h"


MenuSystem::MenuSystem(void)
{
	state = game;
	//schaak = nullptr;
}


MenuSystem::~MenuSystem(void)
{
}

void MenuSystem::processEvent(sf::Event e)
{
	switch(state)
	{
	case game:
		{
			//schaak->processEvent(e);
			//int gs = schaak->gameState();
			//if(gs != GAME_CONTINUE)
			//{
			//	delete schaak;
			//	schaak = nullptr;
			//}
		}
		break;
	case splash:
		//schaak = new Game();
		state = game;
		break;
	}
}

void MenuSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	switch(state)
	{
	case game:
		{
			//Drawables::tDisplay.clear();
			//Drawables::tDisplay.draw(*schaak);
			//Drawables::tDisplay.display();
			
			// determine the offset at which to draw the map.
			//sf::Vector2f drawCentre = schaak->getDrawCentre();
			/*sf::Vector2f targetArea(Interface::windowSize);
			sf::Vector2f sourceArea(sf::Vector2f(MAP_SIZE)*(sf::Vector2f)TILE_SIZE);
			sf::Vector2f drawPosition;
			if(sourceArea.x < targetArea.x)
					drawPosition.x = (targetArea.x - sourceArea.x)/2;
				else if(sourceArea.x == targetArea.x)
					drawPosition.x = 0.f;
				else
					drawPosition.x = std::min(0.f,std::max(-drawCentre.x+targetArea.x/2,-sourceArea.x+targetArea.x));
			
				if(sourceArea.y < targetArea.y)
					drawPosition.y = (targetArea.y - sourceArea.y)/2;
				else if(sourceArea.y == targetArea.y)
					drawPosition.y = 0.f;
				else
					drawPosition.y = std::min(0.f,std::max(-drawCentre.y+targetArea.y/2,-sourceArea.y+targetArea.y));*/




		}
		break;
	case splash:
		//sf::Vector2i offset = (sf::Vector2i(Interface::windowSize) - sf::Vector2i(Drawables::tMainSplash.getSize()))/2;
		//Drawables::mainSplash.setPosition(sf::Vector2f(offset));
		break;
	}
}
