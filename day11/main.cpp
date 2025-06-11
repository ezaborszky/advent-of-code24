#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

std::uint64_t
countStones(std::unordered_map<std::uint64_t, std::uint64_t> &stones,
            int ticker) {
  std::uint64_t numberOfStones = 0;
  for (int x = 0; x < ticker; ++x) {
    std::unordered_map<std::uint64_t, std::uint64_t> changes;

    for (const auto &[key, count] : stones) {

      if (key == 0) {
        changes[1] += count;
      } else if (std::to_string(key).size() % 2 == 0) {
        std::string token = std::to_string(key);
        size_t div = token.length() / 2;
        std::uint64_t firstPart = std::stoull(token.substr(0, div));
        std::uint64_t secondPart = std::stoull(token.substr(div));
        changes[firstPart] += count;
        changes[secondPart] += count;
      } else {
        changes[key * 2024] += count;
      }
    }

    stones = std::move(changes);
  }

  for (const auto &[key, count] : stones) {
    numberOfStones += count;
  }

  return numberOfStones;
}

int main(int argc, char *argv[]) {

  std::unordered_map<std::uint64_t, std::uint64_t> stones;
  std::fstream file("./input");
  std::string token;
  while (file >> token) {
    std::int64_t num = std::stoull(token);
    stones[num]++;
  }

  std::uint64_t sum = 0;
  sum = countStones(stones, 75);
  std::cout << "Number of stones: " << sum << "\n";

  return 0;
}
