#pragma once

#include "Common.h"

class Tank;

class Bullet
{
public:
	Bullet(Tank* owner);
	void Draw();
	void Clear();
	void Tick();
	void Fly();

public:
	float m_fSpeed;
	Tank* m_owner = NULL;
	ETankDir m_dir;

	int pos_x;
	int pos_y;

	clock_t m_curClock;
};
