#include "./game.h"

void PrintMap(int game_map[MAP_SIZE][MAP_SIZE]) {
  for(int row = 0; row < MAP_SIZE; ++row) {
    for(int col = 0; col < MAP_SIZE; ++col) {
      if(game_map[row][col] == SYMBOL_X) {
	std::cout << "X";
      } else if(game_map[row][col] == SYMBOL_O) {
	std::cout << "O";
      } else if(game_map[row][col] == SYMBOL_UNK) {
	std::cout << " ";
      } else {
	std::cout << "Internal Error: Wrong Symbol!" << std::endl;
	std::cout << "Please check your definition!" << std::endl;
	exit(-1);
      }
      std::cout << "|";
    }
    std::cout << std::endl << "-------" << std::endl;
  }
}

bool JudgeWin(int game_map[MAP_SIZE][MAP_SIZE]) {
  // Horizontal
  for(int row = 0; row < MAP_SIZE; ++row) {
      if(game_map[row][0] == game_map[row][1] &&
	 game_map[row][1] == game_map[row][2] &&
	 game_map[row][0] != SYMBOL_UNK) {
	std::cout << "Winner: " << ((game_map[row][0] == SYMBOL_O) ? "O" : "X") << std::endl;
	return true;
      }
  }
  // Vertical
  for(int col = 0; col < MAP_SIZE; ++col) {
    if(game_map[0][col] == game_map[1][col] &&
       game_map[1][col] == game_map[2][col] &&
       game_map[0][col] != SYMBOL_UNK) {
      std::cout << "Winner: " << ((game_map[0][col] == SYMBOL_O) ? "O" : "X") << std::endl;
      return true;
    }
  }
  // Diagonal
  for(int row = 0; row < MAP_SIZE; ++row) {
    for(int col = 0; col < MAP_SIZE; ++col) {
      if(game_map[row][col] == SYMBOL_UNK) continue;
      if(row+2 < MAP_SIZE && col+2 < MAP_SIZE) {
	if(game_map[row][col] == game_map[row+1][col+1] &&
	   game_map[row+1][col+1] == game_map[row+2][col+2]) {
	  std::cout << "Winner: " << ((game_map[row][col] == SYMBOL_O) ? "O" : "X") << std::endl;
	  return true;
	}
      }
      if(row-2 >= 0 && col-2 >= 0) {
	if(game_map[row][col] == game_map[row-1][col-1] &&
	   game_map[row-1][col-1] == game_map[row-2][col-2]) {
	  std::cout << "Winner: " << ((game_map[row][col] == SYMBOL_O) ? "O" : "X") << std::endl;
	  return true;
	}
      }
    }
  }
  return false;
}

bool PlaceSymbol(int symbol, int game_map[MAP_SIZE][MAP_SIZE]) {
  int row, col;
  std::cout << "Symbol: " << ((symbol == SYMBOL_O) ? "O" : "X") << std::endl;
  std::cout << "Please type in the row and col as format: row col" << std::endl;
  std::cin >> row >> col;
  if(row < 0 || col < 0 || row >= MAP_SIZE || col >= MAP_SIZE) {
    std::cout << "Illegal position!" << std::endl;
    return false;
  }
  if(game_map[row][col] != SYMBOL_UNK) {
    std::cout << "Cannot place here!" << std::endl;
    return false;
  }
  game_map[row][col] = symbol;
  return true;
}

void InitMap(int game_map[MAP_SIZE][MAP_SIZE]) {
  for(int row = 0; row < MAP_SIZE; ++row) {
    for(int col = 0; col < MAP_SIZE; ++col) {
      game_map[row][col] = SYMBOL_UNK;
    }
  }
}
