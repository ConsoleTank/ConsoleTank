#ifndef __GAMEMODE_HPP__
#define __GAMEMODE_HPP__

#include "Common.h"

#include "tools.hpp"
#include "Map.hpp"

class GameMode
{
public:
	bool Init()
	{
		tools::ShowCursor(false);
		tools::ChangeEnglish();

		tools::SetWindowSize(120, 40);

		tools::SetTitle(TEXT("̹�˴�ս"));

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
				char ch = _getch();
				if (ch == 'S' || ch == 's')
				{
					cur_sel++;
					if (cur_sel == 4)
						cur_sel = 0;
				}
				else if (ch == 'W' || ch == 'w') {
					cur_sel--;
					if (cur_sel == -1)
						cur_sel = 3;
				}
			}
			string str[4] = { "[1] ����ģʽ","[2] ˫��ģʽ","[3] �༭ģʽ","[4] �˳���Ϸ" };
			for (int i = 0; i <= 3; i++)
			{

				tools::DrawString(TEXT(str[i]), i + 33, 15, i == cur_sel ? 0xF0 : 0x0F);
			}
		}
	}

public:
	Map* m_pmap;
	int cur_sel = 0;
};

#endif // __GAMEMODE_HPP__
