#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <fstream>

#include "Common.h"
#include "tools.hpp"

class Map {
public:
	Map()
	{
	}

	void load_map(string text_name) {
		ifstream fin(text_name);
		for (int i = 0; i < Common::LEN * Common::LEN; i++)
		{
			fin >> map[i];
		}

	}

	void save_map(string text_name) {
		ofstream fout(text_name);
		for (int i = 0; i < Common::LEN*Common::LEN; i++)
		{
			fout << map[i] << ' ';
			if (i % Common::LEN == Common::LEN - 1)
			{
				fout << endl;
			}
		}
	}

	void draw() {
		m_bIsNeedDraw = true;
	}

	void RealDraw()
	{
		if (!m_bIsNeedDraw)
			return;

		m_bIsNeedDraw = false;

		for (int i = 0; i < Common::LEN; i++)
		{
			for (int j = 0; j < Common::LEN; j++)
			{
				int type = map[i * Common::LEN + j];
				switch (type) {
				case Common::WALK:
					tools::DrawString(TEXT("  "), i, j);
					break;
				case Common::WALL:
					tools::DrawString(TEXT("¡ö"), i, j);
					break;
				case Common::GRASS:
					tools::DrawString(TEXT("…d"), i, j, 0x0A);
					break;
				case Common::WATER:
					tools::DrawString(TEXT("¡Ë"), i, j, 0x09);
					break;
				case Common::STONE:
					tools::DrawString(TEXT("¡õ"), i, j);
					break;
				case Common::TANK_ME:
					tools::DrawString(TEXT("¡ö"), i, j, 0x02);
					break;
				case Common::TANK_OTHER:
					tools::DrawString(TEXT("¡ö"), i, j, 0x04);
					break;
				case Common::BULLET_ME:
					tools::DrawString(TEXT("¡ñ"), i, j, 0x02);
					break;
				case Common::BULLET_OTHER:
					tools::DrawString(TEXT("¡ñ"), i, j, 0x04);
					break;
				}
			}
		}

	}

public:
	int map[Common::LEN*Common::LEN] = { 0 };
	bool m_bIsNeedDraw = false;
};

#endif // __GAMEMODE_HPP__