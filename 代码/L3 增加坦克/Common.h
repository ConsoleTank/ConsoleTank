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
	const static int WALK = 0; // ��
	const static int WALL = 1; // ��
	const static int GRASS = 2; // �d
	const static int WATER = 3; // ��
	const static int STONE = 4; // ��

};

#endif // __COMMON_HPP__