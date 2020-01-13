#include <iostream>

#include "tools.hpp"

class GameMode
{
public:
	bool Init()
	{

		tools::ShowCursor(false);

		tools::SetWindowSize(120, 40);

		tools::SetTitle(TEXT("坦克大战"));

		tools::DrawString(TEXT("测试中文English"), 10, 10);

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
		std::cout << "初始化失败" << std::endl;
		return -1;
	}

	mode.Tick();

	system("pause");

}