#ifndef GAME_H_
#define GAME_H_

#include <iostream>

#define MAP_SIZE 3
#define SYMBOL_X 0
#define SYMBOL_O 1
#define SYMBOL_UNK 2

void PrintMap(int game_map[MAP_SIZE][MAP_SIZE]);

bool JudgeWin(int game_map[MAP_SIZE][MAP_SIZE]);

bool PlaceSymbol(int symbol, int game_map[MAP_SIZE][MAP_SIZE]);

void InitMap(int game_map[MAP_SIZE][MAP_SIZE]);

#endif
