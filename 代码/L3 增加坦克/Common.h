#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <Windows.h>
#include <conio.h>
#include <string>
#include <vector>
using namespace std;

class Common {
public:
	const static int LEN = 40;
	const static int WALK = 0; // ¡õ
	const static int WALL = 1; // ¡ö
	const static int GRASS = 2; // …d
	const static int WATER = 3; // ¡Ë
	const static int STONE = 4; // ¡ï

};

#endif // __COMMON_HPP__