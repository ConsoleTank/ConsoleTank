#pragma once
#include "Common.h"
#include "tools.hpp"
class Tank {
public:
	void draw_tank() {
		string str[3] = { "  ¡ö  ","¡ö¡ö¡ö","¡ö  ¡ö" };
		for (int i = 0; i <= 2; i++)
		{
			tools::DrawString(str[i], pos_x + i, pos_y);
		}
	}
	void move(INPUT_RECORD rec) {

		switch (rec.Event.KeyEvent.uChar.AsciiChar)
		{
		case 'w':
		case 'W':
		{
			if (pos_x == 1)
				break;
			else
			{
				pos_x--;
				tools::DrawString("      ", pos_x + 3, pos_y);
			}
			break;
		}
		case's':
		case'S':
		{
			if (pos_x == 36)
				break;
			else 
			{
				pos_x++;
				tools::DrawString("      ", pos_x - 1, pos_y);
			}
			break;
		}
		case'a':
		case'A':
		{
			if (pos_y == 1)
				break;
			else
			{
				pos_y--;
				for (int i = 0;i<= 2;i++)
				{
					tools::DrawString("  ", pos_x + i , pos_y + 3);
				}
			}
			break;
		}


		case'd':
		case'D':
		{
			if (pos_y == 36)
				break;
			else 
			{
				pos_y++;
				for (int i = 0; i <= 2; i++)
				{
					tools::DrawString("  ", pos_x + i, pos_y - 1);
				}
			}
			break;
		}

		}
		draw_tank();
	}
public:
	int pos_x;
	int pos_y;
};