#ifndef __GAMEMODE_HPP__
#define __GAMEMODE_HPP__

#include "Common.h"

#include "tools.hpp"
#include "Map.hpp"

class GameMode
{
public:
	bool Init()
	{
		tools::SetMode();
		tools::ShowCursor(false);
		tools::ChangeEnglish();

		tools::SetWindowSize(120, 40);

		tools::SetTitle(TEXT("坦克大战"));

		m_pmap = new Map();

		m_pmap->load_map("map.txt");
		m_pmap->draw();

		return true;
	}

	void Tick()
	{
		while (true)
		{
			HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

			INPUT_RECORD mouseRec;
			DWORD   res;

			if (ReadConsoleInput(hIn, &mouseRec, 1, &res))
			{
				if (mouseRec.EventType == MOUSE_EVENT)
				{
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
				else if (mouseRec.EventType == KEY_EVENT)
				{
					if (mouseRec.Event.KeyEvent.bKeyDown)
					{
						if(!if_in_game){
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
									exit(0);
								}
								break;
							}
							}
						}
						else {
							switch (mouseRec.Event.KeyEvent.uChar.AsciiChar)
							{
							case '1':
								draw_type = Common::WALL;
								Mode_editor();
								break;
							case '2':
								draw_type = Common::GRASS;
								Mode_editor();
								break;
							case '3':
								draw_type = Common::WATER;
								Mode_editor();
								break;
							case '4':
								draw_type = Common::STONE;
								Mode_editor();
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
				for (int i = 0; i <= 3; i++)
				{

					tools::DrawString("                ", i + 33, 15);
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
		const int paint_pos_x = 10;
		const int paint_pos_y = 48;
		switch (draw_type)
		{
			
		case 1:
			draw_thing = "■";
			tools::DrawString(draw_thing,paint_pos_x, paint_pos_y);
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
	void OnMouseClick(int x, int y)
	{
		if (x <= 0 || x >= 39 || y <= 0 || y >= 39)
			return;
		if (!m_pmap->map[y*Common::LEN + x])
		{
			m_pmap->map[y*Common::LEN + x] = draw_type;
		}
		else {
			m_pmap->map[y*Common::LEN + x] = 0;
		}
		m_pmap->draw();
	}
public:
	Map* m_pmap;
	int cur_sel = 0;
	bool if_in_game = false;
	int draw_type = Common::WALL;
	string draw_thing = "■";
};

#endif // __GAMEMODE_HPP__
