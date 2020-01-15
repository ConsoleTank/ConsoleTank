#pragma once
#include  "Common.h"
#include <time.h>
#include"tools.hpp"
class bullet {
public:
	void draw() {
		tools::DrawString("¡ñ", bul_x , bul_y);
	}

	void clear() {
		tools::DrawString("  ", bul_x, bul_y);
	}

	void tick() {
		end_t = clock();
		float sec = (float)(end_t-begin_t) / CLOCKS_PER_SEC;;
		if (sec >= 0.2)
		{
			begin_t = clock();
			clear();
			fly();
		}
	}

	void fly() {
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
public:
	int bul_x;
	int bul_y;
	ETankDir b_dir;
	int pace = 1;
	clock_t begin_t;
	clock_t end_t;
};