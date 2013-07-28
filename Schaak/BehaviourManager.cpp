#include "BehaviourManager.h"
#include <iostream>
#include <fstream>
#include "common.h"
#include "Logger.h"


BehaviourManager::BehaviourManager(void)
{
	LINFO("Loading behaviours");
	std::ifstream f(AI_BEHAVIOURS_PATH);
	while(f.good())
	{
		std::string filename;
		f >> filename;
		LINFO("Loading behaviour: ");
		LAPPEND(filename);
		Behaviour* b = new Behaviour(AI_PATH + filename);
		behaviours.push_back(b);
	}
}

BehaviourManager::~BehaviourManager(void)
{
}
