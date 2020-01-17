#pragma once

#include "Life.h"

class BaseCamp : public Life
{
public:
	virtual void SetAlive(bool alive);

	void Settlement();

	void Draw();
};
