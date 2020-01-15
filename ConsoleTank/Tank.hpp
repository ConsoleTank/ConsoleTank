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
		for (auto i=my_bullet.begin();i!=my_bullet.end();i++)
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
				GameMode::instance().m_pmap->map[(i + pos_x) * Common::LEN + pos_y + j] = Common::WALK;
			}
		}
	}


	void fire() {
		bullet *bul = new bullet(this);
		my_bullet.push_back( bul);
		bul_num++;

		bul->fire();
	}

	void tank_tick() {

		for (auto i = my_bullet.begin(); i != my_bullet.end(); )
		{

			int tmp_x = (*i)->bul_x;
			int tmp_y= (*i)->bul_y;
			switch ((*i)->b_dir)
			{
			case E_DIR_T:
			{
				tmp_x = (*i)->bul_x - 1;
				break;
			}
			case E_DIR_B:
			{
				tmp_x = (*i)->bul_x + 1;
				break;
			}
			case E_DIR_L:
			{
				tmp_y = (*i)->bul_y-1;
				break;
			}case E_DIR_R:
			{
				tmp_y = (*i)->bul_y+1;
				break;
			}
			}
			int pos_info = GameMode::instance().m_pmap->map[tmp_x* Common::LEN + tmp_y];
			bullet *temp = NULL;
			switch (pos_info) 
			{
			case Common::WALL:
				temp = *i;
				i = my_bullet.erase(i);
				delete temp;
				break;
			case Common::STONE:
				temp = *i;
				i = my_bullet.erase(i);
				delete temp;
				GameMode::instance().m_pmap->map[tmp_x* Common::LEN + tmp_y] = Common::WALK;
				GameMode::instance().m_pmap->draw();

				break;
			default:
				++i;
				break;
			}
				
			
		}
		for (auto i = my_bullet.begin(); i != my_bullet.end(); i++)
		{
			(*i)->tick();
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
		for (auto i = my_bullet.begin(); i != my_bullet.end(); i++)
		{
			(*i) ->clear();
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