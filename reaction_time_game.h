#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#pragma once

#define _LEVELS_NUM 9

// FUNCTIONS

void default_interface();
char random_letter(char last);
void level(HANDLE hConsole, double record[]);
COORD get_middle(HANDLE hConsole);
void level_select();
int load_record(double record[]);
void save_record(double record[]);
void gameplay(HANDLE hConsole, double record[], int difficulty);
void free_mode(HANDLE hConsole);