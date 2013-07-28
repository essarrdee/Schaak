#pragma once
#include <string>
#include <list>
class Behaviour
{
public:
	Behaviour(std::string filename);
	~Behaviour(void);
	std::string name;
	std::list<std::pair<int,int>> values;
	const static int ENEMY_COVER;
	const static int ENEMY_VALUE;
	const static int FRIEND_COVER;
	const static int OWN_VALUE;

};

