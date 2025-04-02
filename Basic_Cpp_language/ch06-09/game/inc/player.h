#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>

class Player {
  std::string player_name;
  int winning_count;

public:
  Player();
  ~Player();
  void setPlayerName(std::string);
  void setWinningCount(int);
  std::string getPlayerName();
  int getWinningCount();
};

#endif
