#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct pair_hash {
  template <typename T1, typename T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    std::size_t h1 = std::hash<T1>()(p.first);
    std::size_t h2 = std::hash<T2>()(p.second);
    return h1 ^ (h2 << 1);
  }
};

struct gardenPatch {
  char letter;
  int sides = 0;
  int size = 0;
  int fullSides = 0;
};

int checkCorners(const std::vector<std::string> &gardenMap,
                 std::pair<int, int> position) {
  // UPLEFT
  int y = position.first;
  int x = position.second;
  int countCorners = 0;
  char gardenType = gardenMap[y][x];

  // map corners
  if (y == 0 && x == 0)
    ++countCorners;
  if (y == 0 && x == gardenMap[y].size() - 1)
    ++countCorners;
  if (y == gardenMap.size() - 1 && x == 0)
    ++countCorners;
  if (y == gardenMap.size() - 1 && x == gardenMap[y].size() - 1)
    ++countCorners;

  // edges
  if (y == 0 && x != 0 && x != gardenMap[y].size() - 1) {
    if (gardenMap[y][x - 1] != gardenType)
      ++countCorners;
    if (gardenMap[y][x + 1] != gardenType)
      ++countCorners;
  }

  if (x == 0 && y != 0 && y != gardenMap.size() - 1) {
    if (gardenMap[y - 1][x] != gardenType)
      ++countCorners;
    if (gardenMap[y + 1][x] != gardenType)
      ++countCorners;
  }

  if (x == gardenMap[y].size() - 1 && y != gardenMap.size() - 1 && y != 0) {
    if (gardenMap[y - 1][x] != gardenType)
      ++countCorners;
    if (gardenMap[y + 1][x] != gardenType)
      ++countCorners;
  }

  if (y == gardenMap.size() - 1 && x != 0 && x != gardenMap[y].size() - 1) {
    if (gardenMap[y][x - 1] != gardenType)
      ++countCorners;
    if (gardenMap[y][x + 1] != gardenType)
      ++countCorners;
  }

  // other
  if (y > 0 && x > 0) {
    // UP LEFT CONVEX
    if (gardenMap[y - 1][x] != gardenType && gardenMap[y][x - 1] != gardenType)
      ++countCorners;
    // UP LEFT CONVEX
    if (gardenMap[y - 1][x] == gardenType &&
        gardenMap[y][x - 1] == gardenType &&
        gardenMap[y - 1][x - 1] != gardenType)
      ++countCorners;
  }

  if (y > 0 && x < gardenMap[y].size() - 1) {
    // UP RIGHT CONVEX
    if (gardenMap[y - 1][x] != gardenType && gardenMap[y][x + 1] != gardenType)
      ++countCorners;
    // UP RIGHT CONVEX
    if (gardenMap[y - 1][x] == gardenType &&
        gardenMap[y][x + 1] == gardenType &&
        gardenMap[y - 1][x + 1] != gardenType)
      ++countCorners;
  }

  if (y < gardenMap.size() - 1 && x > 0) {
    // DOWN LEFT CONVEX
    if (gardenMap[y][x - 1] != gardenType && gardenMap[y + 1][x] != gardenType)
      ++countCorners;
    // DOWN LEFT CONVEX
    if (gardenMap[y][x - 1] == gardenType &&
        gardenMap[y + 1][x] == gardenType &&
        gardenMap[y + 1][x - 1] != gardenType)
      ++countCorners;
  }

  if (x < gardenMap[y].size() - 1 && y < gardenMap.size() - 1) {
    // DOWN RIGHT CONVEX
    if (gardenMap[y][x + 1] != gardenType && gardenMap[y + 1][x] != gardenType)
      ++countCorners;
    // DOWN RIGHT CONVEX
    if (gardenMap[y][x + 1] == gardenType &&
        gardenMap[y + 1][x] == gardenType &&
        gardenMap[y + 1][x + 1] != gardenType)
      ++countCorners;
  }

  return countCorners;
}

int calcFence(
    std::vector<std::string> &gardenMap,
    std::unordered_map<std::pair<int, int>, int, pair_hash> &visitedTiles,
    gardenPatch &newPatch, std::pair<int, int> origo,
    std::pair<int, int> lastOrigo) {
  int directions[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  int y = origo.first;
  int x = origo.second;
  if (visitedTiles.count({y, x}) == 0) {
    visitedTiles[{y, x}] = 1;
    ++newPatch.size;
    int freeSides = 4;
    newPatch.fullSides += checkCorners(gardenMap, origo);

    for (auto dir : directions) {
      if (y + dir[0] >= 0 && y + dir[0] < gardenMap.size() && x + dir[1] >= 0 &&
          x + dir[1] < gardenMap[y].size()) {
        if (gardenMap[y][x] == gardenMap[y + dir[0]][x + dir[1]]) {
          --freeSides;
          calcFence(gardenMap, visitedTiles, newPatch, {y + dir[0], x + dir[1]},
                    origo);
        }
      }
    }
    // I NEED TO FIGURE OUT HERE HOW TO INCREMENT SIDES ONLY WHEN A NEW WHOLE
    // SIDE BEGINS
    newPatch.sides += freeSides;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  std::fstream file("./input");
  std::vector<std::string> lines;
  std::string inputToken;

  while (std::getline(file, inputToken)) {
    lines.push_back(inputToken);
  }

  std::unordered_map<std::pair<int, int>, int, pair_hash> visited;
  std::vector<gardenPatch> foundPatches;

  for (int y = 0; y < lines.size(); ++y) {
    for (int x = 0; x < lines.size(); ++x) {
      if (visited.count({y, x}) == 0) {
        gardenPatch newPatch;
        newPatch.letter = lines[y][x];
        std::pair<int, int> origo = {y, x};
        calcFence(lines, visited, newPatch, origo, origo);
        foundPatches.push_back(newPatch);
      }
    }
  }

  std::int64_t sum = 0;
  std::int64_t rabatAktion = 0;

  for (auto newPatch : foundPatches) {
    // std::cout << "Region: " << newPatch.letter << " price: " << newPatch.size
    //           << " * " << newPatch.fullSides << " = "
    //           << newPatch.fullSides * newPatch.size << ". \n";
    sum += newPatch.size * newPatch.sides;
    rabatAktion += newPatch.fullSides * newPatch.size;
  }

  std::cout << "Old price: " << sum << "\n";
  std::cout << "Bulk price: " << rabatAktion << "\n";

  return 0;
}
