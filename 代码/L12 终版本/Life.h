#pragma once

#include "Common.h"

class Life
{
public:
	Life();
	virtual ~Life();

	virtual void SetAlive(bool alive);
	bool GetAlive() const;

public:

	int pos_x;
	int pos_y;

	ETankDir m_dir;


private:
	bool m_isAlive;
};
