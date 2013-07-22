#include "Logger.h"
#include "Interface.h"

int main(int argc, char** argv)
{
	Logger::init("Schaak.log");
	LINFO("Main started");
	Interface* Schaak = new Interface();
	return 0;

}