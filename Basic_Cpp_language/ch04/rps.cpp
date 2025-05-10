#include <iostream>
#include <random>

int randnum_generator();
enum RPS { ROCK = 1, PAPER, SCISSOR };

int main(int argc, char *argv[]) {
  std::string usr_input, usr_rps;
  RPS rps;

  int comp_opt, usr_win_count, draw, game_count;
  usr_win_count = draw = 0;

  do {
    game_count = 10;

    while (game_count--) {
      std::cout << "Choose your option (rock, paper, scissor): ";
      std::cin >> usr_rps;
      comp_opt = randnum_generator();
      std::cout << "Rock Paper Scissor Shoot! " << std::endl;
      std::cout << comp_opt << std::endl;

      switch (comp_opt) {
      case ROCK:
        if (usr_rps == "rock") {
          draw++;
          std::cout << "Draw!" << std::endl;
        } else if (usr_rps == "paper") {
          std::cout << "You win!" << std::endl;
          usr_win_count++;
        } else {
          std::cout << "You lose!" << std::endl;
        }
        break;
      case PAPER:
        if (usr_rps == "rock") {
          std::cout << "You lose!" << std::endl;
        } else if (usr_rps == "paper") {
          std::cout << "Draw!" << std::endl;
          draw++;
        } else {
          std::cout << "You win!" << std::endl;
          usr_win_count++;
        }
        break;
      case SCISSOR:
        if (usr_rps == "rock") {
          std::cout << "You win!" << std::endl;
          usr_win_count++;
          std::cout << "Draw!" << std::endl;
        } else if (usr_rps == "paper") {
          std::cout << "You lose!" << std::endl;
        } else {
          draw++;
        }
        break;
      }
    }
    std::cout << "<Score Board>" << std::endl;
    std::cout << "Draw games: " << draw << std::endl;
    std::cout << "You: " << usr_win_count
              << " Comp: " << 10 - draw - usr_win_count << std::endl;
    std::cout << "Do you want to play again?(y/n): ";
    std::cin >> usr_input;
  } while (usr_input != "n");

  return 0;
}

int randnum_generator() {
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(1, 3);
  return distrib(gen);
}
