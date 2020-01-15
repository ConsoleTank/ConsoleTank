#pragma once
#include "Common.h"
#include "tools.hpp"

enum ETankDir
{
	E_DIR_T = 0,
	E_DIR_B,
	E_DIR_R,
	E_DIR_L,
};

class Tank {
public:
	void draw_tank() {
		static string out_look[4][3] = { "  ¡ö  ","¡ö¡ö¡ö","¡ö  ¡ö" ,"¡ö  ¡ö","¡ö¡ö¡ö" ,"  ¡ö  " ,"¡ö¡ö  ","  ¡ö¡ö","¡ö¡ö  ","  ¡ö¡ö","¡ö¡ö  ","  ¡ö¡ö" };

		for (int i = 0; i <= 2; i++)
		{
			tools::DrawString(out_look[(int)m_dir][i], pos_x + i, pos_y);
		}
	}

	void clear()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				tools::DrawString("  ", pos_x + i, pos_y + j);
			}
		}
	}

	void move(INPUT_RECORD rec)
	{

		clear();

		switch (rec.Event.KeyEvent.uChar.AsciiChar)
		{
		case 'w':
		case 'W':
		{
			m_dir = E_DIR_T;

			if (pos_x == 1)
				break;
			else
				pos_x--;
			break;
		}
		case's':
		case'S':
		{
			m_dir = E_DIR_B;

			if (pos_x == 36)
				break;
			else 
				pos_x++;
			break;
		}
		case'a':
		case'A':
		{

			m_dir = E_DIR_L;

			if (pos_y == 1)
				break;
			else
				pos_y--;
			break;
		}


		case'd':
		case'D':
		{

			m_dir = E_DIR_R;

			if (pos_y == 36)
				break;
			else 
				pos_y++;
			break;
		}
		}

		draw_tank();
	}

public:
	int pos_x;
	int pos_y;

	ETankDir m_dir;
};