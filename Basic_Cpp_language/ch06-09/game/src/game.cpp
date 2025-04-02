#include "game.h"

Game::Game() {}
Game::~Game() { delete[] players; }
void Game::game_start() {
  std::cout << "How many players are there? ";
  std::cin >> player_num;

  players = new Player[player_num];
  for (int i = 0; i < player_num; i++) {
    std::string name;
    std::cout << "Please enter the player's name: ";
    std::cin >> name;
    players[i].setPlayerName(name);
    players[i].setWinningCount(0);
  }

  bool win = false;
  std::vector<std::string> word_list;
  std::string curr_word = "Tree";
  std::string player_word = "";
  int word_len1 = 0, word_len2 = 0, i = 0;

  while (!win) {
    for (; i < player_num; i++) {
      std::cout << "The Word is " << curr_word << std::endl;
      std::cout << players[i].getPlayerName()
                << ", it's your turn! Enter a word: ";
      std::cin >> player_word;

      int cnt = count(word_list.begin(), word_list.end(), player_word);
      if (curr_word.back() == player_word.front() && cnt <= 0) {
        word_list.push_back(curr_word);
        curr_word = player_word;
      } else {
        if (!win) {
          std::cout << players[i].getPlayerName() << " is eliminated!\n";
          for (int t = i; t < player_num; t++) {
            players[t] = players[t + 1];
          }

          --player_num;
          Player *temp = new Player[player_num];
          for (int j = 0; j < player_num + 1; j++) {
            temp[j] = players[j];
          }

          delete[] players;
          players = temp;
          if (player_num == 1) {
            win = true;
            std::cout << players[0].getPlayerName() << " won!" << std::endl;
            int point = players[0].getWinningCount();
            players[0].setWinningCount(point + 1);
            break;
          }
        }
      }
      std::cout << i << std::endl;
      if (i == player_num - 1)
        i = 0;
    }
  }
}
