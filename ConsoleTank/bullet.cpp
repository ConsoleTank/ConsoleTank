#include "bullet.h"

#include "Tank.hpp"

bullet::bullet(Tank* owner)
{
	m_owner = owner;
}

bullet::~bullet() {
	clear();
	GameMode::instance().m_pmap->draw();
}

void bullet::draw() {
	if (!if_live)
		return;
	if (GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y] != Common::GRASS &&  GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y] != Common::WATER)
	{
		if (m_owner->if_AI)
			GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y] = Common::BULLET;
		else 
			GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y] = Common::M_BULLET;
	}
	GameMode::instance().m_pmap->draw();

}

void bullet::clear() {
	if (GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y] == Common::GRASS || GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y] == Common::WATER || GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y] == Common::WALL)
		return;
	GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y] = Common::WALK;
}

void bullet::fire()
{
	b_dir = m_owner->m_dir;

	switch (b_dir)
	{
	case E_DIR_T:
		bul_x = m_owner->pos_x - 1;
		bul_y = m_owner->pos_y + 1;
		break;
	case E_DIR_B:
		bul_x = m_owner->pos_x + 3;
		bul_y = m_owner->pos_y + 1;
		break;
	case E_DIR_R:
		bul_x = m_owner->pos_x + 1;
		bul_y = m_owner->pos_y + 3;
		break;
	case E_DIR_L:
		bul_x = m_owner->pos_x + 1;
		bul_y = m_owner->pos_y - 1;
		break;
	}
	if_live = true;
	if (GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y] == Common::WALL)
		if_live = false;

	if (if_live)
	{
		draw();
		begin_t = clock();
	}
}

void bullet::check() {
	int tmp_x = bul_x;
	int tmp_y = bul_y;
	switch (b_dir)
	{
	case E_DIR_T:
	{
		tmp_x = bul_x - 1;
		break;
	}
	case E_DIR_B:
	{
		tmp_x = bul_x + 1;
		break;
	}
	case E_DIR_L:
	{
		tmp_y = bul_y - 1;
		break;
	}case E_DIR_R:
	{
		tmp_y = bul_y + 1;
		break;
	}
	}
	int now_pos = GameMode::instance().m_pmap->map[tmp_x* Common::LEN + tmp_y];
	switch (now_pos)
	{
	case Common::WALL:
		if_live = false;
		break;
	case Common::STONE:
		GameMode::instance().m_pmap->map[tmp_x* Common::LEN + tmp_y] = Common::WALK;
		GameMode::instance().m_pmap->draw();
		if_live = false;
		break;
	case Common::BULLET:
	case Common::M_BULLET:
		if_live = false;
		break;
	case Common::TANK:
	case Common::M_TANK:
		if_live = false;
		int tank_pos_x;
		int tank_pos_y;
		for (int i = 0; i < GameMode::instance().left_viral_num; i++)
		{
			tank_pos_x = GameMode::instance().competitior[i]->pos_x;
			tank_pos_y = GameMode::instance().competitior[i]->pos_y;

			if (!GameMode::instance().competitior[i]->if_live_tank)
				continue;
			
			if (GameMode::instance().competitior[i]->if_AI == m_owner->if_AI)
				continue;

			if (bul_x >= tank_pos_x - 1 && bul_x <= tank_pos_x + 3 &&
				bul_y >= tank_pos_y - 1 && bul_y <= tank_pos_y + 3)
			{
				GameMode::instance().competitior[i]->if_live_tank = false;
				GameMode::instance().competitior[i]->clear();
				GameMode::instance().competitior[i]->dead_time = clock();
				m_owner->kill_tanks++;
				GameMode::instance().competitior[i]->dead_times++;
			}


		}
		break;
	default:
		if_live = true;
		break;
	}
}

void bullet::tick() {
	if (if_live)
	{
		check();
		end_t = clock();
		float sec = (float)(end_t - begin_t) / CLOCKS_PER_SEC;;
		if (sec >= 0.01f)
		{
			begin_t = clock();
			clear();
			fly();
		}
	}
}

void bullet::fly() {
	if (!if_live)
		return;
	switch (b_dir) {
	case E_DIR_T:
		bul_x--;
		draw();
		break;
	case E_DIR_B:
		bul_x++;
		draw();
		break;
	case E_DIR_R:
		bul_y++;
		draw();
		break;
	case E_DIR_L:
		bul_y--;
		draw();
		break;
	}
}
