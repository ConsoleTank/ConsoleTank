
#include "GameMode.h"

int main()
{
	if (!GameMode::instance().Init())
	{
		std::cout << "��ʼ��ʧ��" << std::endl;
		return -1;
	}

	GameMode::instance().Tick();

	GameMode::instance().finish();
}