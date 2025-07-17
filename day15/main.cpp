#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::pair<int, int> operator+(const std::pair<int, int> &a,
                              const std::pair<int, int> &b) {
  return {a.first + b.first, a.second + b.second};
}

std::pair<int, int> interpreter(const char &input) {
  std::pair<int, int> outPut = {0, 0};
  if (input == '<') {
    outPut = {0, -1};
  } else if (input == '>') {
    outPut = {0, 1};
  } else if (input == '^') {
    outPut = {-1, 0};
  } else if (input == 'v') {
    outPut = {1, 0};
  }

  return outPut;
}

bool checkMove(std::vector<std::string> &map, std::pair<int, int> direction,
               std::pair<int, int> &currentLocation) {
  std::pair<int, int> targetLocation = currentLocation + direction;
  auto targetChar = map[targetLocation.first][targetLocation.second];
  auto currentChar = map[currentLocation.first][currentLocation.second];

  if (targetChar == '#')
    return false;

  if (targetChar == '.') {
    map[targetLocation.first][targetLocation.second] =
        map[currentLocation.first][currentLocation.second];
    map[currentLocation.first][currentLocation.second] = '.';
    if (currentChar == '@')
      currentLocation = targetLocation;
    return true;
  }

  if (targetChar == 'O') {
    bool couldMove = checkMove(map, direction, targetLocation);
    if (couldMove) {
      map[targetLocation.first][targetLocation.second] = currentChar;
      map[currentLocation.first][currentLocation.second] = '.';
      if (currentChar == '@')
        currentLocation = targetLocation;
      return true;
    }
  }

  return false;
}

int main(int argc, char *argv[]) {

  std::fstream file("./input");
  bool whiteSpaceReached = false;
  std::string bufferString;
  std::vector<std::string> instructions;
  std::vector<std::string> layout;

  while (std::getline(file, bufferString)) {
    if (bufferString.length() < 2)
      whiteSpaceReached = true;
    if (!whiteSpaceReached) {
      layout.push_back(bufferString);
    }

    if (whiteSpaceReached)
      instructions.push_back(bufferString);
  }

  std::pair<int, int> currentLoc;

  for (size_t y = 0; y < layout.size(); ++y) {
    bool innerLoopBroke = false;
    for (size_t x = 0; x < layout[y].size(); ++x) {
      if (layout[y][x] == '@') {
        currentLoc = {y, x};
        innerLoopBroke = true;
        break;
      }
      if (innerLoopBroke)
        break;
    }
  }

  for (auto line : instructions) {
    for (auto dir : line) {
      std::pair<int, int> direction = interpreter(dir);
      checkMove(layout, direction, currentLoc);
    }
  }

  std::int64_t GPSSum = 0;

  for (size_t y = 0; y < layout.size(); ++y) {
    for (size_t x = 0; x < layout[y].size(); ++x) {
      if (layout[y][x] == 'O') {
        GPSSum += (y * 100) + x;
      }
    }
  }
  std::cout << GPSSum << std::endl;
  return 0;
}
