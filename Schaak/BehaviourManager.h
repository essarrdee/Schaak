#pragma once
#include <vector>
#include "Behaviour.h"
class BehaviourManager
{
public:
	BehaviourManager(void);
	~BehaviourManager(void);
	std::vector<Behaviour*> behaviours;
};

