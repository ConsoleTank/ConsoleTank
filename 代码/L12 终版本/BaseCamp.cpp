#include "BaseCamp.h"
#include "tools.hpp"

#include "GameMode.h"

#include <time.h>

void BaseCamp::Draw()
{
	static int info[9] = 
	{
		0,Common::BASE_CAMP,0,
		Common::BASE_CAMP,0,Common::BASE_CAMP,
		0,Common::BASE_CAMP,0
	};

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; j++)
			GameMode::instance().m_pmap->map[(i + pos_x)*Common::LEN + pos_y + j] = info[i * 3 + j];
	}


}

void BaseCamp::SetAlive(bool alive)
{
	Life::SetAlive(alive);

	if (!alive)
	{
		GameMode::instance().gameOver = true;
		GameMode::instance().nt_back = clock();
	}
}

void BaseCamp::Settlement()
{
	tools::DrawString(TEXT("                               "), 18, 12, 0xE4);
	tools::DrawString(TEXT("             提示              "), 19, 12, 0xE4);
	tools::DrawString(TEXT("                               "), 20, 12, 0xE4);
	tools::DrawString(TEXT("                               "), 21, 12, 0xE4);
	tools::DrawString(TEXT("     大本营损坏!游戏结束!       "), 22, 12, 0xE4);
	tools::DrawString(TEXT("                               "), 23, 12, 0xE4);
	tools::DrawString(TEXT("           再接再厉            "), 24, 12, 0xE4);
	tools::DrawString(TEXT("                               "), 25, 12, 0xE4);
	tools::DrawString(TEXT("                               "), 26, 12, 0xE4);
	tools::DrawString(TEXT("                               "), 27, 12, 0xE4);
}