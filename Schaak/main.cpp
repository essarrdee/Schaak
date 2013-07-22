#include "Logger.h"

int main(int argc, char** argv)
{
	Logger::init("Schaak.log");
	LINFO("Main started");
	return 0;
}