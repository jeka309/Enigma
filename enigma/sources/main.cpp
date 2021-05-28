#define NOMINMAX
#include <Windows.h>

#include "MainWindow.h"
#include "ImgCoder.h"

int main(int argc, char* argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	if (argc > 1)
	{
		ImgCoder code(argv[1]);
	}
	else
	{
		MainWindow wnd;
		wnd.Show();
	}

	return 0;
}