#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using yxVec = std::vector<std::pair<int, int>>;
using intGrid = std::vector<std::vector<int>>;

struct PairHash {
  std::size_t operator()(const std::pair<int, int> &p) const {
    return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
  }
};

using ZeroNinePairs =
    std::unordered_map<std::pair<int, int>, std::vector<std::pair<int, int>>,
                       PairHash>;

int searchRoutes(const intGrid &map, const std::pair<int, int> origo,
                 const std::pair<int, int> originalZero,
                 ZeroNinePairs &zerosAndNines) {

  int countedZeros = 0;
  std::vector<std::pair<int, int>> directions = {
      {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  for (auto direction : directions) {
    int dy = origo.first - direction.first;
    int dx = origo.second - direction.second;

    if (dy >= 0 && dy < map.size() && dx >= 0 && dx < map[dy].size()) {

      auto next = map[dy][dx];
      if (next == 9 && map[origo.first][origo.second] + 1 == next) {
        std::pair<int, int> key = originalZero;
        auto &vec = zerosAndNines[key];
        bool contains = std::find(vec.begin(), vec.end(),
                                  std::pair<int, int>{dy, dx}) != vec.end();
        // setting the next condition to !contains solves part1
        if (true) {
          zerosAndNines[key].push_back({dy, dx});
          ++countedZeros;
        }
      } else if (map[origo.first][origo.second] + 1 == next) {
        countedZeros +=
            searchRoutes(map, {dy, dx}, originalZero, zerosAndNines);
      }
    }
  }
  return countedZeros;
}

int main(int argc, char *argv[]) {
  int counter = 0;
  std::fstream file("./input");
  intGrid topMap = {};
  std::string line = "";
  while (std::getline(file, line)) {
    std::vector<int> intLine;
    for (char singleChar : line) {
      intLine.emplace_back(singleChar - '0');
    }
    topMap.push_back(intLine);
  }

  for (auto a : topMap) {
    for (auto b : a) {
      std::cout << b;
    }
    std::cout << "\n";
  }

  yxVec zeroMap;

  for (size_t y = 0; y < topMap.size(); ++y) {
    for (size_t x = 0; x < topMap[y].size(); ++x) {
      if (topMap[y][x] == 0)
        zeroMap.emplace_back(y, x);
    }
  }
  ZeroNinePairs zerosnines;

  for (auto &zero : zeroMap) {
    counter += searchRoutes(topMap, zero, zero, zerosnines);
  }

  std::cout << counter << std::endl;

  return 0;
}
