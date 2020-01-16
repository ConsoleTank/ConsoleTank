#include "bullet.h"

#include "Tank.hpp"

bullet::bullet(Tank* owner)
{
	m_owner = owner;
	m_bIsAlife = true;
}

bullet::~bullet() {
	clear();
	GameMode::instance().m_pmap->draw();
}

void bullet::draw() {
	if (!m_bIsAlife)
		return;

	int type = GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y];
	if (type != Common::GRASS && type != Common::WATER)
		GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y] = Common::BULLET;
	GameMode::instance().m_pmap->draw();

}

void bullet::clear() {
	int type = GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y];
	if (type == Common::WALL ||
		type == Common::GRASS ||
		type == Common::WATER)
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

	begin_t = clock();
	m_bIsAlife = true;

	int pos_info = GameMode::instance().m_pmap->map[bul_x* Common::LEN + bul_y];
	if (pos_info == Common::WALL)
	{
		m_bIsAlife = false;
		return;
	}

	draw();
}

void bullet::tick()
{
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
	int pos_info = GameMode::instance().m_pmap->map[tmp_x* Common::LEN + tmp_y];
	switch (pos_info)
	{
	case Common::WALL:
		m_bIsAlife = false;
		break;
	case Common::STONE:
		m_bIsAlife = false;
		GameMode::instance().m_pmap->map[tmp_x* Common::LEN + tmp_y] = Common::WALK;
		GameMode::instance().m_pmap->draw();
		break;
	}

	end_t = clock();
	float sec = (float)(end_t - begin_t) / CLOCKS_PER_SEC;;
	if (sec >= 0.2)
	{
		begin_t = clock();
		clear();
		fly();
	}
}

void bullet::fly() {
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
