#include <iostream>
#include<vector>
#include "tools.hpp"
#include <string>
using namespace std;
class GameMode
{
public:
	bool Init()
	{

		tools::ShowCursor(false);

		tools::SetWindowSize(120, 40);

		tools::SetTitle(TEXT("̹�˴�ս"));

		tools::DrawString(TEXT("��������English"), 10, 10);

		vector<string> vec = { "  ��  ","������","��  ��" };
		for (int i = 0; i < vec.size(); i++)
		{
			tools::DrawString(vec[i], 0, i);
		}
		tools::DrawString(TEXT("��"), 20, 11);
		tools::DrawString(TEXT("�d"), 20, 12);
		tools::DrawString(TEXT("��"), 20, 13);

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