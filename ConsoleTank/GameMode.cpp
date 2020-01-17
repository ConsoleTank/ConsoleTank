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
	m_pmap->real_draw();
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

	tank01 = NULL;
	tank02 = NULL;

	for (int i = 0; i < left_viral_num; i++)
	{
		delete competitior[i];
		competitior[i] = NULL;
	}

	delete m_pmap;
	m_pmap = NULL;

	return true;
}

void GameMode::Tick()
{
	// while只负责处理菜单
	while (running)
	{
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
		m_pmap->real_draw();
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
		m_pmap->real_draw();
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
void GameMode::multiplayer() {
	left_viral_num = 0;

	static int pos_put_x[4] = { 6,17,30,33 };
	static int pos_put_y[4] = { 32,14,10,5 };

	m_pmap->load_map("battle.txt");
	m_pmap->draw();

	if (!tank01)
		tank01 = new Tank();

	tank01->id = 1;
	tank01->pos_x = 20;
	tank01->pos_y = 20;
	tank01->ori_pos_x = 20;
	tank01->ori_pos_y = 20;
	tank01->if_AI = false;

	competitior[left_viral_num] = tank01;

	left_viral_num++;

	if (!tank02)
		tank02 = new Tank();

	tank02->id = 2;
	tank02->pos_x = 5;
	tank02->pos_y = 10;
	tank02->ori_pos_x = 5;
	tank02->ori_pos_y = 10;
	tank02->if_AI = false;
	competitior[left_viral_num] = tank02;

	if (!m_base)
	{
		m_base = new base();
	}

	m_base->change_live(true);
	m_base->pos_x = 36;
	m_base->pos_y = 18;

	left_viral_num++;

	for (int i = 0; i < 4; i++)
	{
		if (!competitior[left_viral_num])
			competitior[left_viral_num] = new Tank();
		competitior[left_viral_num]->if_AI = true;
		competitior[left_viral_num]->dir = E_DIR_T;
		competitior[left_viral_num]->tank_begin = clock();
		competitior[left_viral_num]->fire_bigin = clock();
		competitior[left_viral_num]->pos_x = pos_put_x[i];
		competitior[left_viral_num]->pos_y = pos_put_y[i];
		competitior[left_viral_num]->ori_pos_x = pos_put_x[i];
		competitior[left_viral_num]->ori_pos_y = pos_put_y[i];
		competitior[left_viral_num]->draw_tank();
		left_viral_num++;
	}

	tank01->draw_tank();
	tank02->draw_tank();

	while (if_in_game)
	{
		if (game_over == false)
		{
			for (int i = 0; i < left_viral_num; i++)
			{
				if (competitior[i]->if_AI && competitior[i]->get_live())
				{
					competitior[i]->viral_move();
					competitior[i]->viral_fire();
				}

				competitior[i]->tank_tick();
			}

			char ch[20];
			sprintf_s(ch, " 击杀数：%d", tank01->kill_tanks);
			tools::DrawString(ch, 10, 42);
			sprintf_s(ch, " 死亡数：%d", tank01->dead_times);
			tools::DrawString(ch, 11, 42);
			sprintf_s(ch, " 击杀数：%d", tank02->kill_tanks);
			tools::DrawString(ch, 12, 42);
			sprintf_s(ch, " 死亡数：%d", tank02->dead_times);
			tools::DrawString(ch, 13, 42);


			if (_kbhit())
			{
				int ch = _getch();

				tank01->ProcessKeyBoard(ch);
				tank02->ProcessKeyBoard(ch);

			}
			m_base->draw();

			m_pmap->real_draw();
		}

		else
		{
			m_base->end_game();
			Sleep(1500);
			ReturnToMainMenu();
		}
	}



}


void GameMode::single_player() {
	left_viral_num = 0;

	static int pos_put_x[4] = { 6,17,30,33 };
	static int pos_put_y[4] = { 32,14,10,5 };

	m_pmap->load_map("battle.txt");
	m_pmap->draw();

	if (!tank01)
		tank01 = new Tank();

	if (!m_base)
	{
		m_base = new base();
	}

	tank01->id = 1;
	tank01->pos_x = 20;
	tank01->pos_y = 20;
	tank01->ori_pos_x = 20;
	tank01->ori_pos_y = 20;
	tank01->if_AI = false;

	m_base->change_live(true);
	m_base->pos_x = 36;
	m_base->pos_y = 18;


	competitior[left_viral_num] = tank01;

	left_viral_num++;

	for (int i = 0; i < 4; i++)
	{
		if (!competitior[left_viral_num])
			competitior[left_viral_num] = new Tank();
		competitior[left_viral_num]->if_AI = true;
		competitior[left_viral_num]->dir = E_DIR_T;
		competitior[left_viral_num]->tank_begin = clock();
		competitior[left_viral_num]->fire_bigin = clock();
		competitior[left_viral_num]->pos_x = pos_put_x[i];
		competitior[left_viral_num]->pos_y = pos_put_y[i];
		competitior[left_viral_num]->ori_pos_x = pos_put_x[i];
		competitior[left_viral_num]->ori_pos_y = pos_put_y[i];
		competitior[left_viral_num]->draw_tank();
		left_viral_num++;
	}

	tank01->draw_tank();


	while (if_in_game)
	{
		if (game_over == false)
		{
			for (int i = 0; i < left_viral_num; i++)
			{
				if (competitior[i]->if_AI && competitior[i]->get_live())
				{
					competitior[i]->viral_move();
					competitior[i]->viral_fire();
				}
				competitior[i]->tank_tick();
			}

			char ch[20];
			sprintf_s(ch, " 击杀数：%d", tank01->kill_tanks);
			tools::DrawString(ch, 10, 42);
			sprintf_s(ch, " 死亡数：%d", tank01->dead_times);
			tools::DrawString(ch, 11, 42);


			if (_kbhit())
			{
				int ch = _getch();
				tank01->ProcessKeyBoard(ch);
			}

			m_base->draw();

			m_pmap->real_draw();
		}
		else
		{
			m_base->end_game();
			Sleep(1500);
			ReturnToMainMenu();
		}
	}
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

	for (int i = 0; i < left_viral_num; i++)
	{
		delete competitior[i];
		competitior[i] = NULL;
	}
	tank01 = NULL;
	if (tank02)
		tank02 = NULL;

	left_viral_num = 0;

	for (int i = 0; i < 4; ++i)
	{
		tools::DrawString(TEXT("            "), 10 + i, 42);
	}
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
			game_over = false;
			if_in_game = true;
			single_player();
			break;
		case 1:
			game_over = false;
			if_in_game = true;
			multiplayer();
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
