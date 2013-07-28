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
};

