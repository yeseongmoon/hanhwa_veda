#include "player.h"

Player::Player() {}
Player::~Player() {}
void Player::setPlayerName(std::string name) { this->player_name = name; }
void Player::setWinningCount(int count) { this->winning_count = count; }
std::string Player::getPlayerName() { return this->player_name; }
int Player::getWinningCount() { return this->winning_count; };
