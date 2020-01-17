#pragma once

#include "Common.h"
#include <time.h>

#include "Life.h"

class Tank;

class bullet : public Life
{
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
	int pace = 1;
	clock_t begin_t;
	clock_t end_t;
	Tank* m_owner;
};