#pragma once
#include "Common.h"
#include "tools.hpp"
#include"bullet.h"
#include "GameMode.h"

class GameMode;

class Tank {
public:
	~Tank()
	{
		for (int i = 0; i < bul_num; ++i)
		{
			delete my_bul[i];
			my_bul[i] = NULL;
		}

		bul_num = 0;
	}

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

	void Move(ETankDir dir)
	{
		clear();

		m_dir = dir;

		switch (dir)
		{
		case E_DIR_T:
		{
			if (pos_x == 1)
				break;
			else
				pos_x--;
			break;
		}
		case E_DIR_B:
		{
			if (pos_x == 36)
				break;
			else
				pos_x++;
			break;
		}
		case E_DIR_L:
		{
			if (pos_y == 1)
				break;
			else
				pos_y--;
			break;
		}
		case E_DIR_R:
		{
			if (pos_y == 36)
				break;
			else
				pos_y++;
			break;
		}
		}

		draw_tank();
	}

	void ProcessKeyBoard(char ch)
	{
		switch (ch)
		{

		case 'j':
		case 'J':
			fire();
			break;

		case 'q':
		case 'Q':
			Exit();
			break;

		case 'w':
		case 'W':
		{
			Move(E_DIR_T);
			break;
		}
		case's':
		case'S':
		{
			Move(E_DIR_B);
			break;
		}
		case'a':
		case'A':
		{
			Move(E_DIR_L);
			break;
		}


		case'd':
		case'D':
		{
			Move(E_DIR_R);
			break;
		}
		}
	}

	void Exit()
	{
		for (int i = 0; i < bul_num; ++i)
		{
			my_bul[i]->clear();
		}

		GameMode::instance().ReturnToMainMenu();
	}

public:
	int pos_x;
	int pos_y;
	bullet *my_bul[100];
	int bul_num;
	ETankDir m_dir;
};