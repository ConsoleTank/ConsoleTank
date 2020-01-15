#pragma once
#include "Common.h"
#include "tools.hpp"
#include "Bullet.h"


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

	void Tick()
	{
		for (std::list<Bullet*>::iterator iter = m_bullets.begin(); iter != m_bullets.end(); ++iter)
		{
			Bullet* bullet = *iter;
			bullet->Tick();
		}
	}

	void Move(ETankDir dir)
	{
		clear();

		switch (dir)
		{
		case E_DIR_T:
			m_dir = E_DIR_T;

			if (pos_x == 1)
				break;
			else
				pos_x--;
			break;

		case E_DIR_B:
			m_dir = E_DIR_B;

			if (pos_x == 36)
				break;
			else
				pos_x++;
			break;

		case E_DIR_L:
			m_dir = E_DIR_L;

			if (pos_y == 1)
				break;
			else
				pos_y--;
			break;

		case E_DIR_R:
			m_dir = E_DIR_R;

			if (pos_y == 36)
				break;
			else
				pos_y++;
			break;

		default:
			break;
		}


		draw_tank();
	}

	void Fire()
	{
		Bullet* bullet = new Bullet(this);
		m_bullets.push_back(bullet);
		bullet->Fly();
	}

	void ProcessEvent(char ch)
	{
		switch (ch)
		{
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

		case 'j':
		case 'J':
			Fire();
			break;
		}
	}

public:
	int pos_x;
	int pos_y;

	ETankDir m_dir;

	std::list<Bullet*> m_bullets;
};