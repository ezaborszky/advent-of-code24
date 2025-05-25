#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <unordered_map>
#include <vector>
using ruleSet = std::pair<int, int>;
using sequenceSet = std::vector<int>;
int main(int argc, char *argv[]) {

  std::fstream file("./input");
  std::vector<ruleSet> rules;
  std::vector<sequenceSet> sequences;
  bool inputSwitch = true;
  std::string line = "";
  int sum = 0;
  while (std::getline(file, line)) {
    std::stringstream stream(line);
    std::string firstToken, secondToken;
    if (line.empty())
      inputSwitch = false;

    if (inputSwitch) {
      std::getline(stream, firstToken, '|');
      std::getline(stream, secondToken, '|');

      int firstNum = std::stoi(firstToken);
      int secondNum = std::stoi(secondToken);
      ruleSet rule = {firstNum, secondNum};
      rules.push_back(rule);
    }

    if (!inputSwitch && !line.empty()) {
      std::vector<int> nums = {};
      while (std::getline(stream, firstToken, ',')) {
        int num = std::stoi(firstToken);
        nums.push_back(num);
      }
      sequences.push_back(nums);
    }
  }

  std::unordered_map<int, std::vector<int>> notBefore;

  for (auto a : rules) {
    notBefore[a.second].push_back(a.first);
  }

  for (size_t index = 0; index < sequences.size(); ++index) {
    bool isLegit = true;
    for (size_t i = 1; i < sequences[index].size(); ++i) {

      for (size_t subindex = 0; subindex < i; ++subindex) {
        for (const auto &num : rules) {
          if (sequences[index][i] == num.first &&
              sequences[index][subindex] == num.second) {
            isLegit = false;
            sequences[index][subindex] = num.first;
            sequences[index][i] = num.second;
          }
        }
      }
    }
    if (!isLegit) {
      int middle = sequences[index][sequences[index].size() / 2];
      sum += middle;
    }
  }

  std::cout << sum << "\n";
  return 0;
}
