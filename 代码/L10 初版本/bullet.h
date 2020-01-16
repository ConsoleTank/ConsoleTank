#pragma once

#include "Common.h"
#include <time.h>

class Tank;

class bullet {
public:
	bullet(Tank* owner);
	~bullet();
	void draw();
	void clear();
	void fire();
	void tick();
	void fly();
	void check();
	void check_tank();

public:
	int bul_x;
	int bul_y;
	ETankDir b_dir;
	int pace = 1;
	clock_t begin_t;
	clock_t end_t;
	bool if_live=true;
	Tank* m_owner;
};