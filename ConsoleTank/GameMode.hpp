#ifndef __GAMEMODE_HPP__
#define __GAMEMODE_HPP__

#include "Common.h"

#include "tools.hpp"
#include "Map.hpp"
#include "Tank.hpp"


class GameMode
{
public:
	void welcome()
	{

		m_pmap->load_map("welcome.txt");
		m_pmap->draw();
		Sleep(1500);

	}
	bool Init()
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

	bool finish() {
		delete m_pmap;
		m_pmap = NULL;

		delete tank01;
		tank01 = NULL;

		return true;
	}

	void Tick()
	{
		while (running)
		{
			HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

			INPUT_RECORD mouseRec;
			DWORD   res;

			if (ReadConsoleInput(hIn, &mouseRec, 1, &res))
			{
				if (mouseRec.EventType == MOUSE_EVENT)
				{
					OnMouse(mouseRec);
				}
				else if (mouseRec.EventType == KEY_EVENT)
				{
					OnKeyBoard(mouseRec);
				}
			}

			if (!if_in_game) {
				string str[4] = { "[1] 单人模式","[2] 双人模式","[3] 编辑模式","[4] 退出游戏" };
				for (int i = 0; i <= 3; i++)
				{

					tools::DrawString(TEXT(str[i]), i + 33, 15, i == cur_sel ? 0xF0 : 0x0F);
				}
			}
			else {
				if (cur_sel == 2)
				{
					Mode_editor_paint_info();

					for (int i = 0; i <= 3; i++)
					{
						tools::DrawString("                ", i + 33, 15);
					}
				}
			}
		}
	}

	void Mode_editor() {

		string str[5] = { "请选择画刷 :","1 .WALL ■","2 .GRASS 卍","3 .WATER ∷","4 .STONE ★" };
		for (int i = 0; i <= 4; i++)
		{
			tools::DrawString(TEXT(str[i]), i + 10, 42);
		}
	}

	void Mode_editor_paint_info()
	{
		const int paint_pos_x = 10;
		const int paint_pos_y = 48;
		string draw_thing = "";
		switch (draw_type)
		{

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

	void single_player() {
		m_pmap->load_map("battle.txt");
		m_pmap->draw();

		if(!tank01)
			tank01 = new Tank();

		tank01->pos_x = 20;
		tank01->pos_y = 20;

		tank01->draw_tank();
	}

	void OnMouse(INPUT_RECORD mouseRec)
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

	void OnKeyBoard_inGame(INPUT_RECORD mouseRec)
	{
		if (cur_sel == 0)
		{
			tank01->move(mouseRec);
		}
		if (cur_sel == 2)
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
				if_in_game = false;
				m_pmap->load_map("map.txt");
				m_pmap->draw();
			}
		}
	}

	void OnKeyBoard_outGame(INPUT_RECORD mouseRec)
	{
		switch (mouseRec.Event.KeyEvent.uChar.AsciiChar)
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

	void OnKeyBoard(INPUT_RECORD mouseRec)
	{
		if (mouseRec.Event.KeyEvent.bKeyDown)
		{
			if (!if_in_game)
				OnKeyBoard_outGame(mouseRec);
			else
				OnKeyBoard_inGame(mouseRec);
		}
	}

	void OnMouseClick(int x, int y)
	{
		if (x <= 0 || x >= 39 || y <= 0 || y >= 39)
			return;

		if (!m_pmap->map[y*Common::LEN + x])
			m_pmap->map[y*Common::LEN + x] = draw_type;
		else
			m_pmap->map[y*Common::LEN + x] = 0;

		m_pmap->draw();
	}
public:
	Map* m_pmap;
	int cur_sel = 0;
	bool if_in_game = false;
	int draw_type = Common::WALL;
	bool running = true;
	Tank *tank01;
};

#endif // __GAMEMODE_HPP__
