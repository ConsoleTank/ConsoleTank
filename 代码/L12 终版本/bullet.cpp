#include "bullet.h"

#include "Tank.hpp"
#include "BaseCamp.h"

bullet::bullet(Tank* owner):Life()
{
	m_owner = owner;
}

bullet::~bullet() {
	clear();

	GameMode::instance().m_pmap->draw();
}

void bullet::draw()
{
	if (!GetAlive())
		return;

	if (GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] != Common::GRASS &&  GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] != Common::WATER)
		GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] = m_owner->m_bIsAI ? Common::BULLET_OTHER : Common::BULLET_ME;
	GameMode::instance().m_pmap->draw();

}

void bullet::clear()
{
	if (GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] == Common::GRASS ||
		GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] == Common::WATER ||
		GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] == Common::WALL ||
		GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] == Common::TANK_ME ||
		GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] == Common::TANK_OTHER)
		return;
	GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] = Common::WALK;
}

void bullet::fire()
{
	m_dir = m_owner->m_dir;

	switch (m_dir)
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
	SetAlive(true);
	if (GameMode::instance().m_pmap->map[pos_x* Common::LEN + pos_y] == Common::WALL)
		SetAlive(false);

	if (GetAlive())
	{
		draw();
		begin_t = clock();
	}
}

void bullet::check_tank()
{
	for (auto tank : GameMode::instance().tanks)
	{
		if (!tank->GetAlive() || !m_owner->GetAlive())
			continue;

		if (tank == m_owner)
			continue;

		if (tank->m_bIsAI == m_owner->m_bIsAI)
			continue;

		if (pos_x >= tank->pos_x &&
			pos_x <= tank->pos_x + 2 &&
			pos_y >= tank->pos_y &&
			pos_y <= tank->pos_y + 2)
		{
			tank->SetAlive(false);
			tank->nt_reborn_t = clock();
			tank->draw_tank();

			tank->m_iCounterDead++;
			m_owner->m_iCounterKill++;
		}
	}

	if (GetAlive())
	{
		auto camp = GameMode::instance().camp;
		if (pos_x >= camp->pos_x &&
			pos_x <= camp->pos_x + 2 &&
			pos_y >= camp->pos_y &&
			pos_y <= camp->pos_y + 2)
		{
			camp->SetAlive(false);
		}
	}
}

void bullet::check() {
	int tmp_x = pos_x;
	int tmp_y = pos_y;
	switch (m_dir)
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
	case Common::BULLET_ME:
	case Common::BULLET_OTHER:
		SetAlive(false);
		break;
	case Common::TANK_ME:
	case Common::TANK_OTHER:
		SetAlive(false);
		break;
	case Common::WALL:
		SetAlive(false);
		break;
	case Common::STONE:
		GameMode::instance().m_pmap->map[tmp_x* Common::LEN + tmp_y] = Common::WALK;
		GameMode::instance().m_pmap->draw();
		SetAlive(false);
		break;
	default:
		SetAlive(true);
		break;
	}
}

void bullet::tick() {
	if (GetAlive())
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

		check_tank();
	}
}

void bullet::fly() {
	switch (m_dir) {
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
