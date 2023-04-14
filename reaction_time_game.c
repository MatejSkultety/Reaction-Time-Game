#include "reaction_time_game.h"
#pragma warning(disable:4996)

void default_interface() {
    system("cls");
    printf("\n\tWelcome to Skuty's reaction time game!\n");
    Sleep(500);
    printf("\n\tBy pressing any key on your keyboard, you start new round of the game.\n");
    printf("\tYou will then choose difficulty level between 1 and 9.\n");
    printf("\tRandom number will show up in a middle of your screen and your task is\n");
    printf("\tpressing corresponding key as fast as possible.\n");
    Sleep(500);
    printf("\n\tBy pressing H this helping menu will show up.\n");
    printf("\n\tPress F for entering free mode.\n");
    printf("\n\tBy pressing ESP you'll leave the game.\n");
    Sleep(500);
    printf("\n\tEnjoy :)\n");
    printf("\n\tPress any key for start or ESC for end: ");
}


void level_select(){
    printf("\n\n\tNow choose, level by pressing key 1 to %d.\n", _LEVELS_NUM);
    printf("\tSelected amount of letters will show up in the middle\n");
    printf("\tof your screen and your job is to hit the keys ASAP.\n");
    printf("\n\tGLHF\n");
    printf("\n\tDifficulty level: ");
}


char random_letter(char last) {
    char random_char = 'A' + rand() % 26;
    if (random_char == last) random_char = random_letter(random_char);
    return random_char;
}


void level(HANDLE hConsole, double record[]) {
    level_select();
    char ch = 0;

    while (ch < '1' || ch > ('0' + _LEVELS_NUM)) {
        ch = _getch();
    }
    int difficulty = ch - '0';

    gameplay(hConsole, record, difficulty);

    printf("\n\n\n\t\tPress ESC to leave, H for help, F for free mode or any other key for restart");
}


COORD get_middle(HANDLE hConsole) {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    int mid_width, mid_height;
    GetConsoleScreenBufferInfo(hConsole, &buffer_info);
    mid_height = (buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1) / 2;
    mid_width = (buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1) / 2;
    COORD point = { mid_width, mid_height };
    return point;
}


int load_record(double record[]) {
    FILE* pRecord = fopen("record.txt", "r");
    if (!pRecord) return 1;
    char buffer[64];
    for (int i = 0; i < _LEVELS_NUM; i++)
    {
        fgets(buffer, 64, pRecord);
        record[i] = strtod(buffer, NULL);
    }
    fclose(pRecord);
    return 0;
}


void save_record(double record[]) {
    FILE* pRecord = fopen("record.txt", "w");
    for (int i = 0; i < _LEVELS_NUM; i++)
    {
        fprintf(pRecord, "%lf\n", record[i]);
    }
    fclose(pRecord);
}


void gameplay(HANDLE hConsole, double record[], int difficulty) {
    clock_t time_start, time_finish;
    double time_total;
    COORD middle = get_middle(hConsole);
    char random_char = '0', ch;
    srand(time(NULL));

    system("cls");
    Sleep(1000);
    time_start = clock();
    for (int i = 0; i < difficulty; i++)
    {
        system("cls");
        random_char = random_letter(random_char);
        SetConsoleCursorPosition(hConsole, middle);
        putchar(random_char);

        do
        {
            if (_kbhit())
            {
                ch = _getch();
                ch = toupper(ch);
                if (ch == random_char) break;
                if (ch == 27) return;
            }
        } while (1 == 1);
    }
    time_finish = clock();
    time_total = (double)(time_finish - time_start) / CLOCKS_PER_SEC;

    if (record[difficulty - 1] == 0 || record[difficulty - 1] > time_total) {
        record[difficulty - 1] = time_total;
        middle.X -= 6;  middle.Y += 2;
        SetConsoleCursorPosition(hConsole, middle);
        printf("*NEW RECORD*");
        middle.X += 6;
        save_record(record);
    }

    middle.X -= 10; middle.Y += 2;
    SetConsoleCursorPosition(hConsole, middle);
    printf("Your time ... %.3lf s", time_total);
    middle.Y += 2;
    SetConsoleCursorPosition(hConsole, middle);
    printf("Best time ... %.3lf s", record[difficulty - 1]);
}


void free_mode(HANDLE hConsole) {
    clock_t time_start, time_finish;
    double time_total, best_time = 5;
    COORD middle = get_middle(hConsole);
    char random_char = '0', ch;
    srand(time(NULL));

    system("cls");
    Sleep(1000);

    while (1 == 1) {
        random_char = random_letter(random_char);
        SetConsoleCursorPosition(hConsole, middle);
        time_start = clock();
        putchar(random_char);

        do
        {
            if (_kbhit())
            {
                ch = _getch();
                ch = toupper(ch);
                if (ch == random_char) {
                    time_finish = clock();
                    time_total = (double)(time_finish - time_start) / CLOCKS_PER_SEC;
                    if (time_total < best_time) best_time = time_total;
                    middle.X -= 10; middle.Y += 2;
                    SetConsoleCursorPosition(hConsole, middle);
                    printf("Your time ... %.3lf s", time_total);
                    middle.Y += 2;
                    SetConsoleCursorPosition(hConsole, middle);
                    printf("Best time ... %.3lf s", best_time);
                    middle.Y += 2;
                    SetConsoleCursorPosition(hConsole, middle);
                    printf("Press ESC to leave", best_time);
                    middle.X += 10; middle.Y -= 6;
                    break;
                }
                if (ch == 27) return;
            }
        } while (1 == 1);
    }
}