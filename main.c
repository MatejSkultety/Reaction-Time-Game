#include "reaction_time_game.h"

int main() {
	char ch = 0;
	double record[_LEVELS_NUM] = {0};
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (load_record(record)) save_record;

	default_interface();
	do
	{
		if (_kbhit()) {
			ch = _getch();
			if (ch == 27) break;  // ESC
			else if (ch == 'h' || ch == 'H') default_interface();
			else if (ch == 'f' || ch == 'F') { free_mode(hConsole); default_interface(); }
			else {
				level(hConsole, record);
			}
		}
	} while (1 == 1);
	printf("\n\n\tEnding . . .\n");

	save_record(record);

	return 0;
}