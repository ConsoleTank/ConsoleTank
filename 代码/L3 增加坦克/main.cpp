
#include "GameMode.hpp"

int main()
{
	GameMode mode;
	if (!mode.Init())
	{
		std::cout << "³õÊ¼»¯Ê§°Ü" << std::endl;
		return -1;
	}

	mode.Tick();

	mode.finish();
}