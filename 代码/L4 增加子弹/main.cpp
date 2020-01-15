
#include "GameMode.hpp"

int main()
{
	if (!GameMode::instance().Init())
	{
		std::cout << "³õÊ¼»¯Ê§°Ü" << std::endl;
		return -1;
	}

	GameMode::instance().Tick();

	GameMode::instance().Fini();
}