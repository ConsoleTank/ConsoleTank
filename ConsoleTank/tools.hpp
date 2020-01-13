#include <iostream>
#include <Windows.h>
#include <string>

class tools
{
public:
	static void ShowCursor(bool isShow)
	{
		CONSOLE_CURSOR_INFO stcCursorInfo;
		stcCursorInfo.bVisible = isShow;
		stcCursorInfo.dwSize = sizeof(stcCursorInfo);
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &stcCursorInfo);
	}

	static void ChangeEnglish()
	{
		keybd_event(VK_SHIFT, 0, 0, 0);
		Sleep(100);
		keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
	}

	static void SetTitle(const std::string& title)
	{
		SetConsoleTitle(title.c_str());
	}

	static bool SetWindowSize(short width, short height)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

		COORD pos = GetLargestConsoleWindowSize(hStdOut);
		COORD BufferSize = { pos.X + 1,pos.Y + 1 };
		if (!SetConsoleScreenBufferSize(hStdOut, BufferSize))
		{
			std::cout << "buffer err ("
				<< BufferSize.X << "," << BufferSize.Y << ")"
				<< GetLastError()
				<< std::endl;
			return false;
		}

		SMALL_RECT srctWindow = { 0, 0, width, height };
		if (!SetConsoleWindowInfo(hStdOut, true, &srctWindow))
		{
			std::cout << "size err " << GetLastError() << std::endl;
			return false;
		}

		COORD Buffer = { width + 1, height + 1 };
		if (!SetConsoleScreenBufferSize(hStdOut, Buffer))
		{
			std::cout << "buffer err ("
				<< BufferSize.X << "," << BufferSize.Y << ")"
				<< GetLastError()
				<< std::endl;
			return false;
		}

		return true;
	}

	static void DrawString(const std::string& str, short x, short y, WORD color = 0x0f)
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, color);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { y * 2, x });
		std::cout << str;
	}
};