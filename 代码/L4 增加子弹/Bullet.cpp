#include "Bullet.h"
#include "Tank.hpp"

Bullet::Bullet(Tank* owner) : m_fSpeed(0.5f), m_owner(owner)
{

}

void Bullet::Clear()
{
	tools::DrawString(TEXT("  "), pos_x, pos_y);
}

void Bullet::Draw()
{
	tools::DrawString(TEXT("¡ñ"), pos_x, pos_y);
}

void Bullet::Tick()
{
	if (m_curClock <= 0)
		return;

	clock_t c = clock();
	float dTime = (float)(c - m_curClock) / CLOCKS_PER_SEC;
	if (dTime > m_fSpeed)
	{
		m_curClock = c;

		Clear();

		switch (m_dir)
		{
		case E_DIR_T:
			pos_x--;
			break;
		case E_DIR_B:
			pos_x++;
			break;
		case E_DIR_R:
			pos_y++;
			break;
		case E_DIR_L:
			pos_y--;
			break;
		default:
			break;
		}

		Draw();
	}
}

void Bullet::Fly()
{
	m_dir = m_owner->m_dir;

	pos_x = m_owner->pos_x + 1;
	pos_y = m_owner->pos_y + 1;

	switch (m_dir)
	{
	case E_DIR_T:
		pos_x -= 2;
		break;

	case E_DIR_B:
		pos_x += 2;
		break;

	case E_DIR_L:
		pos_y -= 2;
		break;

	case E_DIR_R:
		pos_y += 2;
		break;
	}

	m_curClock = clock();

	Draw();
}
