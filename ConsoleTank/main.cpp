#include <iostream>

#include "tools.hpp"

class GameMode
{
public:
	bool Init()
	{

		tools::ShowCursor(false);

		tools::SetWindowSize(120, 40);

		tools::SetTitle(TEXT("̹�˴�ս"));

		tools::DrawString(TEXT("��������English"), 10, 10);

		return true;
	}

	void Tick()
	{

	}
};

int main()
{
	GameMode mode;
	if (!mode.Init())
	{
		std::cout << "��ʼ��ʧ��" << std::endl;
		return -1;
	}

	mode.Tick();

	system("pause");

}