#ifndef __GAMEMODE_HPP__
#define __GAMEMODE_HPP__

#include "Common.h"
#include "base.h"

#include "tools.hpp"
#include "Map.hpp"

class Tank;

class GameMode
{
private:
	static GameMode s_instance;

public:
	static GameMode& instance();

	void welcome();
	bool Init();

	bool finish();

	void Tick();

	void Mode_editor();

	void Mode_editor_paint_info();
	void single_player();
	void OnMouse(INPUT_RECORD mouseRec);
	void OnKeyBoard_Editor(INPUT_RECORD mouseRec);
	void ReturnToMainMenu();
	void OnKeyBoard_Menu(char ch);
	void OnMouseClick(int x, int y);
	void multiplayer();

public:
	Map* m_pmap;
	int cur_sel = 0;
	bool if_in_game = false;
	int draw_type = Common::WALL;
	bool running = true;
	Tank *tank01;
	Tank *tank02;
	Tank *competitior[6];
	int left_viral_num=0;
	bool game_over=false;
	base *m_base;
};


#endif // __GAMEMODE_HPP__
