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
					tools::DrawString(TEXT("…d"), i, j);
					break;
				case Common::WATER:
					tools::DrawString(TEXT("¡Ë"), i, j);
					break;
				case Common::STONE:
					tools::DrawString(TEXT("¡ï"), i, j);
					break;
				}
			}
		}

	}

public:
	int map[Common::LEN*Common::LEN] = { 0 };
};

#endif // __GAMEMODE_HPP__