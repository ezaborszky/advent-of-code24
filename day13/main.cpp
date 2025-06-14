#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct Game {
  std::pair<std::uint64_t, std::uint64_t> buttonA;
  std::pair<std::uint64_t, std::uint64_t> buttonB;
  std::pair<std::uint64_t, std::uint64_t> prize;
};

std::pair<std::uint64_t, std::uint64_t> tokeniser(std::string &input) {
  // std::cout << input << "\n";
  std::stringstream ss(input);
  std::string token;
  std::uint64_t x, y;

  if (input[0] == 'B') {
    std::getline(ss, token, '+');
    std::getline(ss, token, ',');
    x = std::stoi(token);
    std::getline(ss, token, '+');
    std::getline(ss, token);
    y = std::stoi(token);
  } else if (input[0 == 'P']) {
    std::getline(ss, token, '=');
    std::getline(ss, token, ',');
    x = std::stoi(token);
    std::getline(ss, token, '=');
    std::getline(ss, token);
    y = std::stoi(token);
  } else {
    std::cout << "Invalid input! \n";
  }
  return {x, y};
}

std::uint64_t calculateGames(Game &game) {
  if (true) {
    game.prize.first += 10000000000000;
    game.prize.second += 10000000000000;
  }

  std::int64_t Ax = game.buttonA.first;
  std::int64_t Ay = game.buttonA.second;
  std::int64_t Bx = game.buttonB.first;
  std::int64_t By = game.buttonB.second;
  std::int64_t Px = game.prize.first;
  std::int64_t Py = game.prize.second;

  std::int64_t det = Ax * By - Ay * Bx;

  if (det == 0) {
    return 0;
  }

  std::int64_t x_numer = Px * By - Py * Bx;
  std::int64_t y_numer = Ax * Py - Ay * Px;

  if (x_numer % det != 0 || y_numer % det != 0) {
    return 0;
  }

  std::int64_t x = x_numer / det;
  std::int64_t y = y_numer / det;

  return 3 * x + y;
}

int main(int argc, char *argv[]) {

  std::string inputToken;
  std::fstream file("./input");
  std::vector<Game> gamesList;
  std::uint64_t linerCounter = 3;
  Game newGame;
  while (std::getline(file, inputToken)) {

    if (linerCounter == 3) {
      newGame.buttonA = tokeniser(inputToken);
    } else if (linerCounter == 2) {
      newGame.buttonB = tokeniser(inputToken);
    } else if (linerCounter == 1) {
      newGame.prize = tokeniser(inputToken);
    } else {
      gamesList.push_back(newGame);
      linerCounter = 4;
    }
    --linerCounter;
  }
  gamesList.push_back(newGame);
  std::uint64_t finalSum = 0;
  for (auto game : gamesList) {
    std::cout << "Butto A: X+" << game.buttonA.first << " Y+"
              << game.buttonA.second << "\nButton B: X+" << game.buttonB.first
              << " Y+" << game.buttonB.second
              << "\nPrize: X=" << game.prize.first << " Y=" << game.prize.second
              << "\n";
    finalSum += calculateGames(game);
  }
  std::cout << finalSum << "\n";
  return 0;
}
