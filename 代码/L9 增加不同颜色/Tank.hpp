#pragma once
#include "Common.h"
#include "tools.hpp"
#include"bullet.h"
#include "GameMode.h"
#include <list>
#include "Map.hpp"
class GameMode;

class Tank {
public:
	~Tank()
	{
		for (auto i = my_bullet.begin(); i != my_bullet.end(); i++)
		{
			delete (*i);
			(*i) = NULL;
		}

		my_bullet.clear();

		bul_num = 0;
	}


	void draw_tank() {
		if (!if_live)
		{
			clear();
			return;
		}

		int tank = Common::TANK_ME;
		static int tank_map[4][9] = {
		{0,tank,0,tank,tank,tank,tank,0,tank},
		{tank,0,tank,tank,tank,tank,0,tank,0} ,
		{0,tank,tank,tank,tank,0,0,tank,tank},
		{tank,tank,0,0,tank,tank,tank,tank,0}
		};

		tank = Common::TANK_OTHER;
		static int tank_map_ai[4][9] = {
		{0,tank,0,tank,tank,tank,tank,0,tank},
		{tank,0,tank,tank,tank,tank,0,tank,0} ,
		{0,tank,tank,tank,tank,0,0,tank,tank},
		{tank,tank,0,0,tank,tank,tank,tank,0}
		};


		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (GameMode::instance().m_pmap->map[(i + pos_x)*Common::LEN + pos_y + j] == Common::GRASS)
					continue;

				if(m_bIsAI)
					GameMode::instance().m_pmap->map[(i + pos_x)*Common::LEN + pos_y + j] = tank_map_ai[(int)m_dir][i * 3 + j];
				else
					GameMode::instance().m_pmap->map[(i + pos_x)*Common::LEN + pos_y + j] = tank_map[(int)m_dir][i * 3 + j];
			}
		}

		GameMode::instance().m_pmap->draw();

	}

	void clear()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (GameMode::instance().m_pmap->map[(i + pos_x)*Common::LEN + pos_y + j] == Common::GRASS ||
					GameMode::instance().m_pmap->map[(i + pos_x)*Common::LEN + pos_y + j] == Common::BULLET_ME ||
					GameMode::instance().m_pmap->map[(i + pos_x)*Common::LEN + pos_y + j] == Common::BULLET_OTHER)
					continue;
				GameMode::instance().m_pmap->map[(i + pos_x) * Common::LEN + pos_y + j] = Common::WALK;
			}
		}
	}


	void fire() {
		if (!if_live)
			return;

		if (!m_bIsAI)
		{
			clock_t cur = clock();
			float dTime = (float)(cur - nt_fire_t) / CLOCKS_PER_SEC;
			if (dTime < m_fSpeedAttack_Player)
				return;

			nt_fire_t = cur;
		}


		bullet *bul = new bullet(this);
		my_bullet.push_back(bul);
		bul_num++;

		bul->fire();
	}

	void tank_tick()
	{
		for (auto i = my_bullet.begin(); i != my_bullet.end(); i++)
		{
			(*i)->tick();
		}

		for (auto i = my_bullet.begin(); i != my_bullet.end(); )
		{
			bullet *temp = NULL;
			if (!(*i)->if_live)
			{
				temp = *i;
				i = my_bullet.erase(i);
				delete temp;
				temp = NULL;
			}
			else {
				++i;
			}
		}

		if (m_bIsAI && if_live)
		{
			clock_t cur = clock();
			float dTime = (float)(cur - nt_move_t) / CLOCKS_PER_SEC;
			if (dTime > m_fSpeedMove)
			{
				nt_move_t = cur;
				Move(m_dir);
			}

			dTime = (float)(cur - nt_fire_t) / CLOCKS_PER_SEC;
			if (dTime > m_fSpeedAttack)
			{
				nt_fire_t = cur;
				fire();
			}
		}
	}

	bool judge(int x, int y, bool if_col) {
		{
			for (int i = 0; i < 3; i++)
			{

				int judge_op = 0;
				if (!if_col)
					judge_op = GameMode::instance().m_pmap->map[x* Common::LEN + y + i];
				else
					judge_op = GameMode::instance().m_pmap->map[(x + i)* Common::LEN + y];
				if (judge_op == Common::STONE || judge_op == Common::WALL || judge_op == Common::WATER || judge_op == Common::TANK_ME || judge_op == Common::TANK_OTHER || judge_op == Common::BULLET_ME || judge_op == Common::BULLET_OTHER)
				{
					return false;
				}
			}
			return true;
		}

	}

	void Move(ETankDir dir)
	{
		if (!if_live)
			return;

		clear();

		m_dir = dir;

		if (!m_bIsAI)
		{
			clock_t cur = clock();
			float dTime = (float)(cur - nt_move_t) / CLOCKS_PER_SEC;
			if (dTime < m_fSpeedMove)
			{
				draw_tank();
				return;
			}

			nt_move_t = cur;
		}

		bool found = false;
		switch (dir)
		{
		case E_DIR_T:
		{
			if (!judge(pos_x - 1, pos_y, false))
			{
				found = true;
				break;
			}
			else
				pos_x--;
			break;
		}
		case E_DIR_B:
		{
			if (!judge(pos_x + 3, pos_y, false))
			{
				found = true;
				break;
			}
			else
				pos_x++;
			break;
		}
		case E_DIR_L:
		{
			if (!judge(pos_x, pos_y - 1, true))
			{
				found = true;
				break;
			}
			else
				pos_y--;
			break;
		}
		case E_DIR_R:
		{
			if (!judge(pos_x, pos_y + 3, true))
			{
				found = true;
				break;
			}
			else
				pos_y++;
			break;
		}
		}

		if (m_bIsAI && found)
		{
			int value = int(m_dir + 1);
			if (value > int(ETankDir::E_DIR_R))
				value = 0;
			m_dir = ETankDir(value);
			Move(m_dir);
			return;
		}

		draw_tank();
	}

	void ProcessKeyBoard(char ch)
	{
		if (!if_live)
			return;

		if (m_bIsAI)
			return;

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
		for (auto i = my_bullet.begin(); i != my_bullet.end(); i++)
		{
			(*i)->clear();
		}
		GameMode::instance().ReturnToMainMenu();
	}

public:
	int pos_x;
	int pos_y;
	list <bullet*>my_bullet;
	int bul_num;
	ETankDir m_dir;
	bool m_bIsAI = false;
	clock_t nt_move_t;
	clock_t nt_fire_t;

	float m_fSpeedMove = 0.3f;
	float m_fSpeedAttack = 1.0f;
	float m_fSpeedAttack_Player = 0.5f;

	bool if_live = true;


};