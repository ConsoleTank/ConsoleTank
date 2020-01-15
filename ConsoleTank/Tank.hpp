#pragma once
#include "Common.h"
#include "tools.hpp"
#include"bullet.h"
#include "GameMode.h"

class GameMode;

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


	void fire() {
		bullet *bul = new bullet(this);
		my_bul[bul_num] = bul;
		bul_num++;

		bul->fire();
	}

	void tank_tick() {
		for(int i = 0; i < bul_num; i++)
		{
			my_bul[i]->tick();
		}
	}

	void ProcessKeyBoard(char ch)
	{
		clear();

		switch (ch)
		{

		case 'j':
		case 'J':
			fire();
			break;

		case 'q':
		case 'Q':
			GameMode::instance().ReturnToMainMenu();
			break;

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
	bullet *my_bul[100];
	int bul_num;
	ETankDir m_dir;
};