#include <iostream>

class GameMode
{
public:
	bool Init()
	{
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
		std::cout << "³õÊ¼»¯Ê§°Ü" << std::endl;
		return -1;
	}

	mode.Tick();

	system("pause");
}