#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
using ruleSet = std::pair<int, int>;
using sequenceSet = std::vector<int>;
int main(int argc, char *argv[]) {

  std::fstream file("./input");
  std::vector<ruleSet> rules;
  std::vector<sequenceSet> sequences;
  bool inputSwitch = true;
  std::string line = "";

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

  for (auto a : rules) {
    std::cout << "{ " << a.first << " | " << a.second << " } \n";
  }

  for (auto a : sequences) {
    std::cout << "[ ";
    for (auto b : a) {
      std::cout << b << ",";
    }
    std::cout << "] \n";
  }
  return 0;
}
