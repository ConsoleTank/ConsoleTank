#pragma once

#include "Common.h"
#include <time.h>
#include"element.h"

class Tank;

class bullet :public element {
public:
	bullet(Tank* owner);
	~bullet();
	void draw();
	void clear();
	void fire();
	void tick();
	void fly();
	void check();

public:
	int pace = 1;
	clock_t begin_t;
	clock_t end_t;
	Tank* m_owner;
};