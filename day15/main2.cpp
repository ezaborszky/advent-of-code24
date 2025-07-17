#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

void debug() { std::cout << "Works! \n"; }

struct pair_hash {
  std::size_t operator()(const std::pair<int, int> &p) const {
    return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
  }
};

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
               std::pair<int, int> &position, bool &robotMove) {

  std::pair<int, int> targetPos = position + direction;
  auto targetChar = map[targetPos.first][targetPos.second];
  auto currentChar = map[position.first][position.second];
  bool couldMove1, couldMove2, couldMove3, couldMove4;
  bool asd = true;
  if (currentChar == '@') {
    if (targetChar == '#')
      return false;

    if (targetChar == '[' || targetChar == ']') {

      couldMove1 = checkMove(map, direction, targetPos, asd);
      if (couldMove1)
        targetChar = '.';
    }

    if (targetChar == '.') {
      map[targetPos.first][targetPos.second] = currentChar;
      map[position.first][position.second] = '.';
      position = targetPos;
      robotMove = true;
    }
  }

  if (currentChar == '[' || currentChar == ']') {

    if (targetChar == '#')
      return false;
    if (currentChar == '[') {
      if (map[targetPos.first][targetPos.second + 1] == '#')
        return false;
    } else if (currentChar == ']') {
      if (map[targetPos.first][targetPos.second - 1] == '#')
        return false;
    }

    if (targetChar == '[' || targetChar == ']') {
      couldMove2 = checkMove(map, direction, targetPos, asd);
      if (couldMove2)
        targetChar = '.';
    }

    if (targetChar == '.') {
      if (currentChar == '[' && abs(direction.first) > 0) {
        couldMove3 = true;
        if (map[targetPos.first][targetPos.second + 1] == '#')
          return false;
        std::pair<int, int> altPos = {targetPos.first, targetPos.second + 1};
        if (map[targetPos.first][targetPos.second + 1] == '[')
          couldMove3 = checkMove(map, direction, altPos, asd);
        if (map[targetPos.first][targetPos.second + 1] == '.')
          couldMove3 = true;
        if (couldMove3) {
          map[targetPos.first][targetPos.second] = currentChar;
          map[targetPos.first][targetPos.second + 1] = ']';
          map[position.first][position.second] = '.';
          map[position.first][position.second + 1] = '.';
          return true;
        }
      }
      if (currentChar == ']' && abs(direction.first) > 0) {
        couldMove4 = true;
        if (map[targetPos.first][targetPos.second - 1] == '#')
          return false;
        std::pair<int, int> altPos = {targetPos.first, targetPos.second - 1};
        if (map[targetPos.first][targetPos.second - 1] == ']')
          couldMove4 = checkMove(map, direction, altPos, asd);
        if (map[targetPos.first][targetPos.second - 1] == '.')
          couldMove4 = true;
        if (couldMove4) {
          map[targetPos.first][targetPos.second] = currentChar;
          map[targetPos.first][targetPos.second - 1] = '[';
          map[position.first][position.second] = '.';
          map[position.first][position.second - 1] = '.';
          return true;
        }
      }

      if ((currentChar == '[' || currentChar == ']') &&
          abs(direction.first) == 0) {
        map[targetPos.first][targetPos.second] = currentChar;
        map[position.first][position.second] = '.';
        return true;
      }
    }
  }
  return false;
}

void printMap(std::vector<std::string> map) {
  for (auto y : map) {
    for (auto x : y) {
      std::cout << x;
    }
    std::cout << "\n";
  }
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
  std::vector<std::string> newLayout;

  for (size_t y = 0; y < layout.size(); ++y) {
    std::string line = "";
    for (size_t x = 0; x < layout[y].size(); ++x) {
      if (layout[y][x] == '#' || layout[y][x] == '.') {
        line.push_back(layout[y][x]);
        line.push_back(layout[y][x]);
      } else if (layout[y][x] == '@') {
        currentLoc = {y, x * 2};
        line.push_back('@');
        line.push_back('.');
      } else if (layout[y][x] == 'O') {
        line.push_back('[');
        line.push_back(']');
      }
    }
    newLayout.push_back(line);
  }
  // printMap(newLayout);
  for (auto line : instructions) {
    for (auto command : line) {
      // std::cout << command << "\n";
      std::pair<int, int> dir = interpreter(command);
      std::vector<std::string> copy = newLayout;
      bool robot = false;
      checkMove(newLayout, dir, currentLoc, robot);
      if (!robot)
        newLayout = copy;
      // printMap(newLayout);
    }
  }
  int sum = 0;

  for (size_t y = 0; y < newLayout.size(); ++y) {
    for (size_t x = 0; x < newLayout[y].size(); ++x) {
      if (newLayout[y][x] == '[') {
        int gps = y * 100 + x;
        sum += gps;
      }
    }
  }

  std::cout << sum << "\n";
  return 0;
}
