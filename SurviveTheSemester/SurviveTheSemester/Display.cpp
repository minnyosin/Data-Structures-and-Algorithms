// This Display.cpp file is 100% AI Generated.
// This does not interfear with any of the logic that is implemented.
// This is used just to make the display of the narrative fancy.

#include "Display.h"
#include <iostream>
#include <windows.h>

using namespace std;

void enableSkipInput()
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	DWORD mode = 0;
	GetConsoleMode(hIn, &mode);

	// Turn on mouse click events, and turn off "Quick Edit" mode
	// (which would otherwise eat clicks for text selection instead
	// of letting us see them).
	mode |= ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
	mode &= ~ENABLE_QUICK_EDIT_MODE;

	SetConsoleMode(hIn, mode);
}

// Non-blocking check: has the player pressed Space/Enter or clicked
// the mouse since we last looked? Returns immediately either way.
static bool skipWasRequested()
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	DWORD numEvents = 0;
	GetNumberOfConsoleInputEvents(hIn, &numEvents);
	if (numEvents == 0)
		return false;

	INPUT_RECORD records[64];
	DWORD read = 0;
	ReadConsoleInput(hIn, records, 64, &read);

	bool skip = false;
	for (DWORD i = 0; i < read; i++)
	{
		if (records[i].EventType == KEY_EVENT && records[i].Event.KeyEvent.bKeyDown)
		{
			WORD key = records[i].Event.KeyEvent.wVirtualKeyCode;
			if (key == VK_SPACE || key == VK_RETURN)
				skip = true;
		}
		else if (records[i].EventType == MOUSE_EVENT &&
			(records[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED))
		{
			skip = true;
		}
	}
	return skip;
}

void slowPrint(const string& text, int delayMs)
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	// Ignore any clicks/keys the player made before this line started,
	// so an old input doesn't instantly skip the new line.
	FlushConsoleInputBuffer(hIn);

	bool skipping = false;
	for (size_t i = 0; i < text.size(); i++)
	{
		if (!skipping && skipWasRequested())
			skipping = true;

		cout << text[i] << flush;

		if (!skipping)
			Sleep(delayMs);
	}
	cout << endl;

	// Don't let clicks/keys from this line bleed into whatever reads
	// input next (like the menu's cin >>).
	FlushConsoleInputBuffer(hIn);
}
