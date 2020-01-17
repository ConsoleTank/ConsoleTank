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
	if (!get_live())
		return;
	if (GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] != Common::GRASS &&  GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] != Common::WATER)
	{
		if (m_owner->if_AI)
			GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] = Common::BULLET;
		else 
			GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] = Common::M_BULLET;
	}
	GameMode::instance().m_pmap->draw();

}

void bullet::clear() {
	if (GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] == Common::GRASS || GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] == Common::WATER || GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] == Common::WALL)
		return;
	GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] = Common::WALK;
}

void bullet::fire()
{
	dir = m_owner->dir;

	switch (dir)
	{
	case E_DIR_T:
		pos_x = m_owner->pos_x - 1;
		pos_y = m_owner->pos_y + 1;
		break;
	case E_DIR_B:
		pos_x = m_owner->pos_x + 3;
		pos_y = m_owner->pos_y + 1;
		break;
	case E_DIR_R:
		pos_x = m_owner->pos_x + 1;
		pos_y = m_owner->pos_y + 3;
		break;
	case E_DIR_L:
		pos_x = m_owner->pos_x + 1;
		pos_y = m_owner->pos_y - 1;
		break;
	}
	change_live(true);
	if (GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] == Common::WALL)
		change_live(false);

	if (get_live())
	{
		draw();
		begin_t = clock();
	}
}

void bullet::check() {
	int tmp_x = pos_x;
	int tmp_y = pos_y;
	switch (dir)
	{
	case E_DIR_T:
	{
		tmp_x = pos_x - 1;
		break;
	}
	case E_DIR_B:
	{
		tmp_x = pos_x + 1;
		break;
	}
	case E_DIR_L:
	{
		tmp_y = pos_y - 1;
		break;
	}case E_DIR_R:
	{
		tmp_y = pos_y + 1;
		break;
	}
	}
	int now_pos = GameMode::instance().m_pmap->map[tmp_x* Common::LEN + tmp_y];
	switch (now_pos)
	{
	case Common::WALL:
		change_live(false);
		break;
	case Common::STONE:
		GameMode::instance().m_pmap->map[tmp_x* Common::LEN + tmp_y] = Common::WALK;
		GameMode::instance().m_pmap->draw();
		change_live(false);
		break;
	case Common::BULLET:
	case Common::M_BULLET:
		change_live(false);
		break;
	case Common::TANK:
	case Common::M_TANK:
		change_live(false);
		int tank_pos_x;
		int tank_pos_y;
		for (int i = 0; i < GameMode::instance().left_viral_num; i++)
		{
			tank_pos_x = GameMode::instance().competitior[i]->pos_x;
			tank_pos_y = GameMode::instance().competitior[i]->pos_y;

			if (!GameMode::instance().competitior[i]->get_live())
				continue;
			
			if (GameMode::instance().competitior[i]->if_AI == m_owner->if_AI)
				continue;

			if (pos_x >= tank_pos_x - 1 && pos_x <= tank_pos_x + 3 &&
				pos_y >= tank_pos_y - 1 && pos_y <= tank_pos_y + 3)
			{
				GameMode::instance().competitior[i]->change_live(false);
				GameMode::instance().competitior[i]->clear();
				GameMode::instance().competitior[i]->dead_time = clock();
				m_owner->kill_tanks++;
				GameMode::instance().competitior[i]->dead_times++;
			}


		}
		break;
	case Common::BASE:
	{
		GameMode::instance().m_base->change_live(false);
		break;
	}
	default:
		change_live(true);
		break;
	}
}

void bullet::tick() {
	if (get_live())
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
	if (!get_live())
		return;
	switch (dir) {
	case E_DIR_T:
		pos_x--;
		draw();
		break;
	case E_DIR_B:
		pos_x++;
		draw();
		break;
	case E_DIR_R:
		pos_y++;
		draw();
		break;
	case E_DIR_L:
		pos_y--;
		draw();
		break;
	}
}
