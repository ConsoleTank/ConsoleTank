#include <iostream>
#include<vector>
#include "tools.hpp"
#include <string>
#include<fstream>
#include "Common.h"
using namespace std;
class Map {
public:
	Map()
	{
	}

	int map[Common::len*Common::len] = { 0 };
	void load_map(string text_name) {
		ifstream fin(text_name);
		for (int i = 0; i < Common::len * Common::len; i++)
		{
			fin >> map[i];
		}
		
	}
	void save_map(string text_name) {
		ofstream fout(text_name);
		for (int i = 0; i < Common::len*Common::len; i++)
		{
			fout << map[i];
			if (i % Common::len == Common::len-1)
			{
				fout << endl;
			}
		}
	}
	void draw() {
		for (int i = 0; i < Common::len ; i++)
		{
			for (int j = 0; j < Common::len; j++)
			{
				int type = map[i * Common::len + j];
				switch (type) {
				case Common::walk:
					tools::DrawString(TEXT("  "), i, j);
					break;
				case Common::wall:
					tools::DrawString(TEXT("■"), i, j);
					break;
				case Common::grass:
					tools::DrawString(TEXT("卍"), i, j);
					break;
				case Common::water:
					tools::DrawString(TEXT("∷"), i, j);
					break;
				case Common::stone:
					tools::DrawString(TEXT("★"), i, j);
					break;
				}
			}
		}
		
	}
};
class GameMode
{
public:
	Map* m_pmap;
	int cur_sel=0;
	bool Init()
	{

		tools::ShowCursor(false);

		tools::SetWindowSize(120, 40);

		tools::SetTitle(TEXT("坦克大战"));

		/*tools::DrawString(TEXT("测试中文English"), 10, 10);

		vector<string> vec = { "  ■  ","■■■","■  ■" };
		for (int i = 0; i < vec.size(); i++)
		{
			tools::DrawString(vec[i], 0, i, 0x0C);
		}
		tools::DrawString(TEXT("□"), 20, 11, 0xCE);
		tools::DrawString(TEXT("卍"), 20, 12);
		tools::DrawString(TEXT("∷"), 20, 13);*/

		m_pmap = new Map();
		
		
		m_pmap->load_map("map.txt");
		m_pmap->draw();
		return true;
	}

	void Tick()
	{
		while (true)
		{
			if (_kbhit())
			{
				char ch=_getch();
				if (ch == 'S' || ch=='s')
				{
					cur_sel++;
					if (cur_sel == 4)
						cur_sel = 0;
				}
				else if(ch=='W' || ch=='w'){
					cur_sel--;
					if (cur_sel == -1)
						cur_sel = 3;
				}
			}
			string str[4] = { "[1] 单人模式","[2] 双人模式","[3] 编辑模式","[4] 退出游戏" };
			for (int i = 0; i <= 3; i++)
			{
				
				tools::DrawString(TEXT(str[i]), i+33, 15, i == cur_sel ? 0xF0 : 0x0F);
			}
		}
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