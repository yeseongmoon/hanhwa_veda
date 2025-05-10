#ifndef _GAME_H_
#define _GAME_H_

#include "player.h"
#include <iostream>
#include <vector>

class Game {
  Player *players;
  int player_num;

public:
  Game();
  ~Game();
  void game_start();
};

#endif
