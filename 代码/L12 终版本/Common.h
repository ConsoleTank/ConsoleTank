#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <Windows.h>
#include <conio.h>
#include <string>
#include <list>
using namespace std;

enum ETankDir
{
	E_DIR_T = 0,
	E_DIR_B,
	E_DIR_L,
	E_DIR_R,
};
class Common {
public:
	const static int LEN = 40;
	const static int WALK = 0; // ��
	const static int WALL = 1; // ��
	const static int GRASS = 2; // �d
	const static int WATER = 3; // ��
	const static int STONE = 4; // ��
	const static int TANK_ME = 50;
	const static int TANK_OTHER = 51; // ����̹��
	const static int BULLET_ME = 60;
	const static int BULLET_OTHER = 61;
	const static int BASE_CAMP = 70; // ��


};

#endif // __COMMON_HPP__