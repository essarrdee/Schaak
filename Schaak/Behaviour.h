#pragma once
#include <string>
#include <list>

const int ENEMY_COVER = 0;
const int ENEMY_VALUE = 1;
const int FRIEND_COVER = 2;
const int OWN_VALUE = 3;

class Behaviour
{
public:
	Behaviour(std::string filename);
	~Behaviour(void);
	std::string name;
	std::list<std::pair<int,int>> values;

};

