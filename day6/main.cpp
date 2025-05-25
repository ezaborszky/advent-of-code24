#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

int main(int argc, char *argv[]) {

  std::fstream file("./input");
  std::vector<std::string> rows;
  std::string line = "";
  int steps = 0;
  while (std::getline(file, line)) {
    rows.push_back(line);
  }

  struct coordinates {
    int x = 0;
    int y = 0;

    bool operator<(const coordinates &other) const {
      return (x == other.x) ? (y < other.y) : (x < other.x);
    }
  };
  int loops = 0;
  coordinates curPos;

  coordinates forbiddenTile = {curPos.x - 1, curPos.y};
  std::set<coordinates> visited;

  enum directions { UP, DOWN, LEFT, RIGHT };
  directions currentDir = UP;

  for (size_t i = 0; i < rows.size(); ++i) {
    for (size_t letter = 0; letter < rows[i].size(); ++letter) {
      if (rows[i][letter] == '^') {

        curPos.x = i;
        curPos.y = letter;
      }
    }
  }
  coordinates startPos = curPos;
  coordinates lastPos = {-1, -1};
  char lastValue = '\0';

  for (size_t x = 0; x < rows.size(); ++x) {
    for (size_t y = 0; y < rows[0].size(); ++y) {

      if (x == startPos.x && y == startPos.y)
        continue;

      if (lastPos.x != -1 && lastPos.y != -1)
        rows[lastPos.x][lastPos.y] = lastValue;

      lastValue = rows[x][y];
      rows[x][y] = '#';
      lastPos = {static_cast<int>(x), static_cast<int>(y)};

      // ------------------------------------
      // TESTING
      //
      bool inBoundaries = true;
      currentDir = UP;
      curPos = startPos;
      std::set<std::tuple<int, int, directions>> visitedStates;

      while (inBoundaries) {

        auto state = std::make_tuple(curPos.x, curPos.y, currentDir);
        if (visitedStates.count(state)) {
          ++loops;
          std::cout << "Loops: " << loops << std::endl;
          inBoundaries = false;
          break;
        }

        visitedStates.insert(state);

        // UP
        if (currentDir == UP) {
          if (curPos.x > 0) {
            if (rows[curPos.x - 1][curPos.y] == '#') {
              currentDir = RIGHT;
            } else {
              curPos.x -= 1;
              ++steps;
            }
          }

          if (curPos.x == 0)
            inBoundaries = false;
        }

        // RIGHT
        if (currentDir == RIGHT) {
          if (curPos.y + 1 < rows[0].size()) {
            if (rows[curPos.x][curPos.y + 1] == '#') {
              currentDir = DOWN;
            } else {
              curPos.y += 1;
              ++steps;
            }
          }

          if (curPos.y + 1 == rows[0].size()) {
            inBoundaries = false;
          }
        }

        // DOWN
        if (currentDir == DOWN) {
          if (curPos.x + 1 < rows.size()) {
            if (rows[curPos.x + 1][curPos.y] == '#') {
              currentDir = LEFT;
            } else {
              curPos.x += 1;
              ++steps;
            }
          }

          if (curPos.x + 1 == rows.size()) {
            inBoundaries = false;
          }
        }

        // LEFT
        if (currentDir == LEFT) {
          if (curPos.y > 0) {
            if (rows[curPos.x][curPos.y - 1] == '#') {
              currentDir = UP;
            } else {
              curPos.y -= 1;
              ++steps;
            }
          }

          if (curPos.y == 0) {
            inBoundaries = false;
          }
        }
      }
    }
  }
  std::cout << loops << std::endl;
  return 0;
}
