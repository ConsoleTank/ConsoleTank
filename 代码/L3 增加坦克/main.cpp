
#include "GameMode.hpp"

int main()
{
	GameMode mode;
	if (!mode.Init())
	{
		std::cout << "��ʼ��ʧ��" << std::endl;
		return -1;
	}

	mode.Tick();

	mode.finish();
}