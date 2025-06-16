#include "game.h"

int main(int argc, char **argv) {
  int game_map[MAP_SIZE][MAP_SIZE];
  int curr_symbol = SYMBOL_X;
  InitMap(game_map);

  while(1) {
    PrintMap(game_map);
    // X first
    while(!PlaceSymbol(curr_symbol, game_map)) {
      PrintMap(game_map);
    }
    if(JudgeWin(game_map)) {
      PrintMap(game_map);
      break;
    }
    curr_symbol = (curr_symbol == SYMBOL_X) ? SYMBOL_O : SYMBOL_X;
  }
  
  return 0;
}
