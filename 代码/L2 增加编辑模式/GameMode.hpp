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

		m_bIsEnterGame = false;

		return true;
	}

	void Tick()
	{
		while (true)
		{
			if (_kbhit())
			{
				char ch = _getch();
				if (!m_bIsEnterGame)
				{
					if (ch == 'S' || ch == 's')
					{
						cur_sel++;
						if (cur_sel == 4)
							cur_sel = 0;
					}
					else if (ch == 'W' || ch == 'w')
					{
						cur_sel--;
						if (cur_sel == -1)
							cur_sel = 3;
					}
				}
			
				// 确定
				if (ch == 'J' || ch == 'j')
				{
					OnOK();
				}
				else if (ch == 'K' || ch == 'k')
				{
					OnCancel();
				}
			}


			if (m_bIsEnterGame && cur_sel == Common::MODE_EDITOR)
			{
				HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

				INPUT_RECORD	mouseRec;
				DWORD			res;

				while (ReadConsoleInput(hIn, &mouseRec, 1, &res))
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
						case MOUSE_MOVED:
							nX = mouseRec.Event.MouseEvent.dwMousePosition.X;
							nY = mouseRec.Event.MouseEvent.dwMousePosition.Y;
							break;
						}
					}
					else if (mouseRec.EventType == KEY_EVENT)
					{
						if (mouseRec.Event.KeyEvent.bKeyDown) {
							switch (mouseRec.Event.KeyEvent.uChar.AsciiChar)
							{
							case '1':
								cur_sel_paint = 1;
								break;
							case '2':
								cur_sel_paint = 2;
								break;
							case '3':
								cur_sel_paint = 3;
								break;
							case '4':
								cur_sel_paint = 4;
								break;

							case 'S':
							case 's':
								OnSaveEditMap();
								break;

							default:
								break;
							}
						}
						break;
					}
					else
					{
						break;
					}
				}

				string text_paint = "";
				switch (cur_sel_paint)
				{
				case Common::WALL:
					text_paint = TEXT("■");
					break;
				case Common::GRASS:
					text_paint = TEXT("卍");
					break;
				case Common::WATER:
					text_paint = TEXT("∷");
					break;
				case Common::STONE:
					text_paint = TEXT("★");
					break;

				default:
					text_paint = TEXT("  ");
					break;
				}
				tools::DrawString(text_paint, 12, 50);
			}


			if (!m_bIsEnterGame)
			{
				string str[4] = { "[1] 单人模式","[2] 双人模式","[3] 编辑模式","[4] 退出游戏" };
				for (int i = 0; i <= 3; i++)
				{
					tools::DrawString(TEXT(str[i]), i + 33, 15, i == cur_sel ? 0xF0 : 0x0F);
				}
			}
			else
			{
				for (int i = 0; i <= 3; i++)
				{
					tools::DrawString(TEXT("  "), i + 33, 15);
				}
			}
		}
	}

	void OnOK()
	{
		switch (cur_sel)
		{
		case Common::MODE_SINGLE:
			m_bIsEnterGame = true;
			break;

		case Common::MODE_DOUBLE:
			m_bIsEnterGame = true;
			break;

		case Common::MODE_EDITOR:
			m_bIsEnterGame = true;
			OnEnterEditMode();
			break;

		case Common::MODE_EXIT:
			if (!m_bIsEnterGame)
				exit(0);

			m_bIsEnterGame = false;
			break;

		default:
			m_bIsEnterGame = false;
			break;
		}
	}

	void OnCancel()
	{

	}

	void OnSaveEditMap()
	{
		m_pmap->save_map("map_editor.txt");

		m_bIsEnterGame = false;

		m_pmap->load_map("map.txt");
		m_pmap->draw();
	}

	void OnEnterEditMode()
	{
		// 第一步: 加载硬盘上的地图文件
		m_pmap->load_map("map_editor.txt");
		m_pmap->draw();

		// 第二步: 绘制右侧的文本信息
		string texts[5] = {
			TEXT("当前选择的画刷:"),
			TEXT("  1: 墙 ■"),
			TEXT("  2: 草 卍"),
			TEXT("  3: 水 ∷"),
			TEXT("  4: 石 ★")
		};
		for (int i = 0; i < 5; ++i)
			tools::DrawString(texts[i], 12 + i, 42);
	}

	void OnMouseClick(short x, short y)
	{
		// 第一步: 边缘检测
		if (x <= 0 || x >= Common::LEN - 1 || y <= 0 || y >= Common::LEN - 1)
			return;

		int type = Common::WALK;
		switch (cur_sel_paint)
		{
		case 1:
			type = Common::WALL;
			break;
		case 2:
			type = Common::GRASS;
			break;
		case 3:
			type = Common::WATER;
			break;
		case 4:
			type = Common::STONE;
			break;
		}

		int last_type = m_pmap->map[y*Common::LEN + x];
		if (last_type == 0)
			m_pmap->map[y*Common::LEN + x] = type;
		else
			m_pmap->map[y*Common::LEN + x] = 0;

		m_pmap->draw();

	}

public:
	Map* m_pmap;
	int cur_sel = 0;
	int cur_sel_paint = 1;
	bool m_bIsEnterGame = false;
};

#endif // __GAMEMODE_HPP__
