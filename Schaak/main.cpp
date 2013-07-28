#include "Logger.h"
#include "Interface.h"
#include <time.h>
#include <random>

int main(int argc, char** argv)
{
	Logger::init("Schaak.log");
	LINFO("Main started");
	srand((unsigned)time(0));
	LINFO("RNG seeded");
	Interface* Schaak = new Interface();
	return 0;
}