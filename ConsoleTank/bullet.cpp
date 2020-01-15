#include "bullet.h"

#include "Tank.hpp"

bullet::bullet(Tank* owner)
{
	m_owner = owner;
}

void bullet::draw() {
	tools::DrawString("¡ñ", bul_x, bul_y);
}

void bullet::clear() {
	tools::DrawString("  ", bul_x, bul_y);
}

void bullet::fire()
{
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
}

void bullet::tick() {
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
