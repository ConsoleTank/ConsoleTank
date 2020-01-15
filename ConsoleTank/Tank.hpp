#pragma once
#include "Common.h"
#include "tools.hpp"
class Tank {
public:
	void draw_tank() {
		
		for (int i = 0; i <= 2; i++)
		{
			tools::DrawString(out_look[now_way][i], pos_x + i, pos_y);
		}
	}
	void clear() {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				tools::DrawString("  ", pos_x + i, pos_y + j);
			}
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
				clear();
				pos_x--;
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
				clear();
				pos_x++;
				
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
				clear();
				pos_y--;
				
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
				clear();
				pos_y++;
				
			}
			break;
		}
		case '1':
			now_way = 0;
			break;
		case'2':
			now_way = 1;
			break;
		case'3':
			now_way = 2;
			break;
		case'4':
			now_way = 3; 
			break;
		}
		draw_tank();
	}
public:
	int pos_x;
	int pos_y;
	string out_look[4][3] = { "  ¡ö  ","¡ö¡ö¡ö","¡ö  ¡ö" ,"¡ö  ¡ö","¡ö¡ö¡ö" ,"  ¡ö  " ,"¡ö¡ö  ","  ¡ö¡ö","¡ö¡ö  ","  ¡ö¡ö","¡ö¡ö  ","  ¡ö¡ö" };
	int now_way = 0;
};