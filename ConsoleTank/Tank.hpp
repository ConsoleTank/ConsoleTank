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
		static int tank_map[4][9] = {
		{0,5,0,5,5,5,5,0,5},
		{5,0,5,5,5,5,0,5,0} ,
		{0,5,5,5,5,0,0,5,5},
		{5,5,0,0,5,5,5,5,0}
		};
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (GameMode::instance().m_pmap->map[(i + pos_x)*Common::LEN + pos_y + j] == Common::GRASS)
					continue;
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
				if (GameMode::instance().m_pmap->map[(i + pos_x)*Common::LEN + pos_y + j] == Common::GRASS)
					continue;
				GameMode::instance().m_pmap->map[(i + pos_x) * Common::LEN + pos_y + j] = Common::WALK;
			}
		}
	}


	void fire() {
		bullet *bul = new bullet(this);
		my_bullet.push_back(bul);
		bul_num++;

		bul->fire();
	}

	void tank_tick() {

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
			}
			else {
				++i;
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
				if (judge_op == Common::STONE || judge_op == Common::WALL || judge_op == Common::WATER)
				{
					return false;
				}
			}
			return true;
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
			if (!judge(pos_x - 1, pos_y, false))
				break;
			else
				pos_x--;
			break;
		}
		case E_DIR_B:
		{
			if (!judge(pos_x + 3, pos_y, false))
				break;
			else
				pos_x++;
			break;
		}
		case E_DIR_L:
		{
			if (!judge(pos_x, pos_y - 1, true))
				break;
			else
				pos_y--;
			break;
		}
		case E_DIR_R:
		{
			if (!judge(pos_x, pos_y + 3, true))
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
};