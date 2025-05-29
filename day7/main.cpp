#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[]) {

  std::fstream file("./input");
  std::string line = "";
  std::unordered_map<std::uint64_t, std::vector<int>> numbers;

  while (std::getline(file, line)) {
    std::string token = "";
    std::stringstream stream(line);
    std::getline(stream, token, ':');
    std::int64_t currentLine;
    currentLine = std::stoull(token);
    numbers[currentLine];
    while (stream >> token) {
      numbers[currentLine].push_back(std::stoi(token));
    }
  }

  std::uint64_t finalResult = 0;

  for (const auto line : numbers) {
    std::uint64_t key = line.first;
    const std::vector<int> &vec = line.second;

    int bitLength = vec.size() - 1;
    int combinations = std::pow(3, bitLength);

    for (const auto &a : vec) {
    }
    bool isLegit = false;
    for (int x = combinations; x >= 0; --x) {
      std::uint64_t sum = vec[0];
      int vectorIndex = 0;

      int opCode = x;
      for (int i = bitLength; i > 0; --i) {
        int op = opCode % 3;
        opCode /= 3;

        if (vectorIndex < bitLength) {
          if (op == 0)
            sum += vec[vectorIndex + 1];
          else if (op == 1)
            sum *= vec[vectorIndex + 1];
          else if (op == 2) {
            std::string a, b;
            a = std::to_string(sum);
            b = std::to_string(vec[vectorIndex + 1]);
            std::string concatd = a + b;
            sum = std::stoull(concatd);
          }
        }

        ++vectorIndex;
      }
      if (key == sum)
        isLegit = true;
    }
    if (isLegit)
      finalResult += key;
  }
  std::cout << finalResult << "\n";
  return 0;
}
