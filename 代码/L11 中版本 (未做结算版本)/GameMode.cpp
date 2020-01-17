#include "GameMode.h"

#include "Tank.hpp"

GameMode GameMode::s_instance;

GameMode& GameMode::instance()
{
	return s_instance;
}

void GameMode::welcome()
{
	m_pmap->load_map("welcome.txt");
	m_pmap->draw();
	m_pmap->RealDraw();
	Sleep(1500);

}

bool GameMode::Init()
{
	tools::SetMode();
	tools::ShowCursor(false);
	tools::ChangeEnglish();

	tools::SetWindowSize(120, 40);

	tools::SetTitle(TEXT("坦克大战"));
	m_pmap = new Map();

	welcome();
	m_pmap->load_map("map.txt");
	m_pmap->draw();

	return true;
}

bool GameMode::finish() {
	delete m_pmap;
	m_pmap = NULL;

	for (auto ele : tanks)
	{
		if (!ele)
		{
			delete ele;
			ele = NULL;
		}
	}

	return true;
}

void GameMode::Tick()
{
	// while只负责处理菜单
	while (running)
	{
		for (int i = 0; i <= 7; i++)
		{
			tools::DrawString("                ", i + 10, 42);
		}

		string str[4] = { "[1] 单人模式","[2] 双人模式","[3] 编辑模式","[4] 退出游戏" };
		for (int i = 0; i <= 3; i++)
		{
			tools::DrawString(TEXT(str[i]), i + 33, 15, i == cur_sel ? 0xF0 : 0x0F);
		}

		if (_kbhit())
		{
			char ch = _getch();
			OnKeyBoard_Menu(ch);
		}

		m_pmap->RealDraw();
	}
}

void GameMode::Mode_editor()
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	INPUT_RECORD mouseRec;
	DWORD   res;

	for (int i = 0; i <= 3; i++)
	{
		tools::DrawString("                ", i + 33, 15);
	}

	string str[5] = { "请选择画刷 :","1 .WALL ■","2 .GRASS 卍","3 .WATER ∷","4 .STONE ★" };
	for (int i = 0; i <= 4; i++)
	{
		tools::DrawString(TEXT(str[i]), i + 10, 42);
	}

	while (if_in_game)
	{
		if (ReadConsoleInput(hIn, &mouseRec, 1, &res))
		{
			if (mouseRec.EventType == MOUSE_EVENT)
			{
				OnMouse(mouseRec);
			}
			else if (mouseRec.EventType == KEY_EVENT)
			{
				OnKeyBoard_Editor(mouseRec);
			}
		}

		Mode_editor_paint_info();

		m_pmap->RealDraw();
	}

}

void GameMode::Mode_editor_paint_info()
{
	const int paint_pos_x = 10;
	const int paint_pos_y = 48;
	string draw_thing = "";
	switch (draw_type)
	{
	case 0:
		draw_thing = " □";
		tools::DrawString(draw_thing, paint_pos_x, paint_pos_y);
		break;
	case 1:
		draw_thing = "■";
		tools::DrawString(draw_thing, paint_pos_x, paint_pos_y);
		break;

	case 2:
		draw_thing = "卍";
		tools::DrawString(draw_thing, paint_pos_x, paint_pos_y);
		break;

	case 3:
		draw_thing = "∷";
		tools::DrawString(draw_thing, paint_pos_x, paint_pos_y);
		break;

	case 4:
		draw_thing = "★";
		tools::DrawString(draw_thing, paint_pos_x, paint_pos_y);
		break;


	}

}

void GameMode::_battle()
{
	m_pmap->draw();

	for (int i = 0; i < 5; ++i)
	{
		Tank* tank = new Tank();
		tank->pos_y = 1 + 8 * i;
		tank->pos_x = 1;
		tank->ori_pos_x = tank->pos_x;
		tank->ori_pos_y = tank->pos_y;
		tank->m_dir = ETankDir::E_DIR_B;
		tank->ori_m_dir = tank->m_dir;
		tank->m_bIsAI = true;
		tank->draw_tank();
		tanks.push_back(tank);
	}

	char tmp[64];

	while (if_in_game)
	{
		for (auto tank : tanks)
			tank->tank_tick();

		if (_kbhit())
		{
			char ch = _getch();

			tank01->ProcessKeyBoard(ch);
			if (tank02)
				tank02->ProcessKeyBoard(ch);
		}

		m_pmap->RealDraw();

		if (tank01)
		{
			tools::DrawString(TEXT("玩家一:"), 10, 42);
			sprintf_s(tmp, TEXT("击杀数 %d"), tank01->m_iCounterKill);
			tools::DrawString(tmp, 11, 44, 0x02);
			sprintf_s(tmp, TEXT("死亡数 %d"), tank01->m_iCounterDead);
			tools::DrawString(tmp, 12, 44, 0x04);
		}
		if (tank02)
		{
			tools::DrawString(TEXT("玩家二:"), 14, 42);
			sprintf_s(tmp, TEXT("击杀数 %d"), tank02->m_iCounterKill);
			tools::DrawString(tmp, 15, 44, 0x02);
			sprintf_s(tmp, TEXT("死亡数 %d"), tank02->m_iCounterDead);
			tools::DrawString(tmp, 16, 44, 0x04);
		}
	}
}

void GameMode::single_player()
{
	m_pmap->load_map("battle.txt");
	tanks.clear();

	if (!tank01)
	{
		tank01 = new Tank();
	}
	tank01->m_bIsAI = false;
	tanks.push_back(tank01);

	tank01->pos_x = 36;
	tank01->pos_y = 13;

	tank01->ori_pos_x = tank01->pos_x;
	tank01->ori_pos_y = tank01->pos_y;
	tank01->m_dir = ETankDir::E_DIR_T;
	tank01->ori_m_dir = tank01->m_dir;

	tank01->draw_tank();

	_battle();
}

void GameMode::double_player()
{
	m_pmap->load_map("battle.txt");
	tanks.clear();

	if (!tank01)
	{
		tank01 = new Tank();
	}
	tank01->m_bIsAI = false;
	tanks.push_back(tank01);

	tank01->pos_x = 36;
	tank01->pos_y = 13;

	tank01->ori_pos_x = tank01->pos_x;
	tank01->ori_pos_y = tank01->pos_y;
	tank01->m_dir = ETankDir::E_DIR_T;
	tank01->ori_m_dir = tank01->m_dir;

	tank01->draw_tank();

	if (!tank02)
	{
		tank02 = new Tank();
	}
	tank02->m_bIsAI = false;
	tanks.push_back(tank02);

	tank02->pos_x = 36;
	tank02->pos_y = 23;

	tank02->ori_pos_x = tank02->pos_x;
	tank02->ori_pos_y = tank02->pos_y;
	tank02->m_dir = ETankDir::E_DIR_T;
	tank02->ori_m_dir = tank02->m_dir;

	tank02->draw_tank();

	_battle();
}

void GameMode::OnMouse(INPUT_RECORD mouseRec)
{
	if (!if_in_game)
		return;

	if (cur_sel != 2)
		return;

	short nX = mouseRec.Event.MouseEvent.dwMousePosition.X / 2;
	short nY = mouseRec.Event.MouseEvent.dwMousePosition.Y;

	switch (mouseRec.Event.MouseEvent.dwEventFlags)
	{
	case 0:
		//左键单击
		if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			OnMouseClick(nX, nY);
		}
		break;

	case MOUSE_MOVED:
		nX = mouseRec.Event.MouseEvent.dwMousePosition.X;
		nY = mouseRec.Event.MouseEvent.dwMousePosition.Y;
		break;
	}
}

void GameMode::OnKeyBoard_Editor(INPUT_RECORD mouseRec)
{

	switch (mouseRec.Event.KeyEvent.uChar.AsciiChar)
	{
	case '1':
		draw_type = Common::WALL;
		break;

	case '2':
		draw_type = Common::GRASS;
		break;

	case '3':
		draw_type = Common::WATER;
		break;

	case '4':
		draw_type = Common::STONE;
		break;

	case 's':
	case 'S':
		m_pmap->save_map("editor.txt");
		ReturnToMainMenu();
		break;

	case 'q':
	case 'Q':
		ReturnToMainMenu();
		break;
	}
}

void GameMode::ReturnToMainMenu()
{
	if_in_game = false;
	m_pmap->load_map("map.txt");
	m_pmap->draw();

	for (auto ele : tanks)
	{
		delete ele;
		ele = NULL;
	}

	tank01 = NULL;
	tank02 = NULL;

	tanks.clear();
}

void GameMode::OnKeyBoard_Menu(char ch)
{
	switch (ch)
	{
	case 'S':
	case 's':
	{
		cur_sel++;
		if (cur_sel == 4)
			cur_sel = 0;
		break;
	}
	case 'W':
	case 'w':
	{
		cur_sel--;
		if (cur_sel == -1)
			cur_sel = 3;
		break;
	}

	case 'J':
	case 'j':
	{
		switch (cur_sel)
		{
		case 0:
			if_in_game = true;
			single_player();
			break;
		case 1:
			if_in_game = true;
			double_player();
			break;
		case 2:
			if_in_game = true;
			m_pmap->load_map("editor.txt");
			m_pmap->draw();
			Mode_editor();
			break;
		case 3:
			if_in_game = false;
			running = false;
			break;
		}
		break;
	}
	}
}

void GameMode::OnMouseClick(int x, int y)
{
	if (x <= 0 || x >= 39 || y <= 0 || y >= 39)
		return;

	if (!m_pmap->map[y*Common::LEN + x])
		m_pmap->map[y*Common::LEN + x] = draw_type;
	else
		m_pmap->map[y*Common::LEN + x] = 0;

	m_pmap->draw();
}
