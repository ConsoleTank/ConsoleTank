#pragma once
#include "Common.h"
#include "tools.hpp"
#include"bullet.h"
#include "GameMode.h"
#include <list>
#include "Map.hpp"


class GameMode;

class Tank: public element{	
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
		static int m_tank_map[4][9] = {
		{0,7,0,7,7,7,7,0,7},
		{7,0,7,7,7,7,0,7,0} ,
		{0,7,7,7,7,0,0,7,7},
		{7,7,0,0,7,7,7,7,0}
		};
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
				int& type = GameMode::instance().m_pmap->map[(i + pos_x)*Common::LEN + pos_y + j];
				if (type == Common::GRASS)
					continue;

				if(if_AI)
					type = tank_map[(int)dir][i * 3 + j];
				else
					type = m_tank_map[(int)dir][i * 3 + j];
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
			if (!(*i)->get_live())
			{
				temp = *i;
				i = my_bullet.erase(i);
				delete temp;
			}
			else {
				++i;
			}
		}
		if (!get_live())
			relive();
	}

	bool judge(int x, int y, bool if_col)
	{
		for (int i = 0; i < 3; i++)
		{

			int judge_op = 0;
			if (!if_col)
				judge_op = GameMode::instance().m_pmap->map[x* Common::LEN + y + i];
			else
				judge_op = GameMode::instance().m_pmap->map[(x + i)* Common::LEN + y];
			if (judge_op == Common::STONE || judge_op == Common::WALL || judge_op == Common::WATER || judge_op == Common::TANK || judge_op == Common::BULLET || judge_op == Common::M_TANK || judge_op == Common::M_BULLET)
			{
				return false;
			}
		}
		return true;
	}


	void Move(ETankDir m_dir)
	{
		if (!get_live())
			return;

		clear();

		dir = m_dir;


		switch (dir)
		{
		case E_DIR_T:
		{
			if (!judge(pos_x - 1, pos_y, false))
			{
				if (!if_AI)
					break;
				else {
					dir = E_DIR_R;
				}
			}
			else
				pos_x--;
			break;
		}
		case E_DIR_B:
		{
			if (!judge(pos_x + 3, pos_y, false))
			{
				if (!if_AI)
					break;
				else {
					dir = E_DIR_L;
				}
			}
			else
				pos_x++;
			break;
		}
		case E_DIR_L:
		{
			if (!judge(pos_x, pos_y - 1, true))

			{
				if (!if_AI)
					break;
				else {
					dir = E_DIR_T;
				}
			}
			else
				pos_y--;
			break;
		}
		case E_DIR_R:
		{
			if (!judge(pos_x, pos_y + 3, true))
			{
				if (!if_AI)
					break;
				else {
					dir = E_DIR_B;
				}
			}
			else
				pos_y++;
			break;
		}
		}

		draw_tank();
	}

	void ProcessKeyBoard(int ch)
	{
		if (!get_live())
			return;

		if (if_AI)
			return;


		switch (ch)
		{

		case 'j':
		case 'J':
			if (id == 1)
				fire();
			break;
		case 'l':
		case'L':
			if (id == 2)
				fire();
			break;

		case 'q':
		case 'Q':
			Exit();
			break;

		case 'w':
		case 'W':
		{
			if (id == 1)
				Move(E_DIR_T);
			break;
		}
		case's':
		case'S':
		{
			if (id == 1)
				Move(E_DIR_B);
			break;
		}
		case'a':
		case'A':
		{
			if (id == 1)
				Move(E_DIR_L);
			break;
		}


		case'd':
		case'D':
		{
			if (id == 1)
				Move(E_DIR_R);
			break;
		}
		case 72:
		{
			if (id == 2)
				Move(E_DIR_T);
			break;
		}
		case 80:
		{
			if (id == 2)
				Move(E_DIR_B);
			break;
		}
		case 75:
		{
			if (id == 2)
				Move(E_DIR_L);
			break;
		}
		case 77:
		{
			if (id == 2)
				Move(E_DIR_R);
			break;
		}
		}

	}
	void viral_move() {
		if (!if_AI)
			return;
		tank_move_time = clock();
		float sec = (float)(tank_move_time - tank_begin) / CLOCKS_PER_SEC;;
		if (sec >= .5f)
		{
			tank_begin = clock();
			Move(dir);
		}
	}

	void viral_fire() {
		if (!if_AI)
			return;
		fire_end = clock();
		float sec = (float)(fire_end - fire_bigin) / CLOCKS_PER_SEC;;
		if (sec >= 1.0f)
		{
			fire_bigin = clock();
			fire();
		}
	}

	void relive() {
		again_time = clock();
		float sec = (float)(again_time - dead_time) / CLOCKS_PER_SEC;;
		if (sec >= 5.0)
		{
			change_live(true);
			pos_x = ori_pos_x;
			pos_y = ori_pos_y;
			draw_tank();
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
	list <bullet*>my_bullet;
	int bul_num;
	bool if_AI;
	clock_t tank_begin;
	clock_t tank_move_time;
	clock_t fire_bigin;
	clock_t fire_end;
	clock_t dead_time;
	clock_t again_time;
	int dead_times;
	int kill_tanks;
	int ori_pos_x;
	int ori_pos_y;
	int id;

};