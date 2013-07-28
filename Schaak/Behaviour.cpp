#include "Behaviour.h"
#include <iostream>
#include <fstream>
#include "Logger.h"

const int Behaviour::ENEMY_COVER = 0;
const int Behaviour::ENEMY_VALUE = 1;
const int Behaviour::FRIEND_COVER = 2;
const int Behaviour::OWN_VALUE = 3;

Behaviour::Behaviour(std::string filename)
{
	std::fstream f(filename);
	f >> name;
	LINFO("Name: ");
	LAPPEND(name);
	while(f.good())
	{
		std::string evalType;
		f >> evalType;
		std::pair<int,int> valuePair;
		if(evalType == "enemy_cover")
		{
			valuePair.first = ENEMY_COVER;
		}
		else if(evalType == "enemy_value")
		{
			valuePair.first = ENEMY_VALUE;
		}
		else if(evalType == "friend_cover")
		{
			valuePair.first = FRIEND_COVER;
		}
		else if(evalType == "own_value")
		{
			valuePair.first = OWN_VALUE;
		}
		f >> valuePair.second;
		values.push_back(valuePair);
	}
}


Behaviour::~Behaviour(void)
{
}
