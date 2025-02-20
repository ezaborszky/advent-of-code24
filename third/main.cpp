#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

int main(int argc, char *argv[]) {
  int valids = 0;
  std::fstream file("./input.md");
  std::string line = "";
  std::vector<int> values = {};
  std::vector<std::vector<int>> tableOfValues;
  while (std::getline(file, line)) {
    std::stringstream ss;
    int num = 0;
    ss << line;
    while (ss >> num) {
      values.push_back(num);
    }
    tableOfValues.push_back(values);
    values.clear();
  }

  for (auto numberLine : tableOfValues) {
    bool isValid = false;
    int lineLenght = numberLine.size();

    for (size_t i = 0; i < numberLine.size() - 1; ++i) {
      int firstNum = numberLine[i];
      int secondNum = numberLine[i + 1];
      int difference = abs(firstNum - secondNum);
      if (difference > 0 && difference <= 3 && secondNum >= firstNum) {
        isValid = true;
      } else {
        isValid = false;
        break;
      }
      if (!isValid)
        break;
    }

    if (!isValid) {
      for (size_t i = 0; i < numberLine.size() - 1; ++i) {
        int firstNum = numberLine[i];
        int secondNum = numberLine[i + 1];
        int difference = abs(firstNum - secondNum);
        if (difference > 0 && difference <= 3 && secondNum <= firstNum) {
          isValid = true;
        } else {
          isValid = false;
          break;
        }
        if (!isValid)
          break;
      }
    }

    if (!isValid) {
      for (int i = 0; i < numberLine.size(); ++i) {
        std::vector<int> temporaryVec = {};
        for (auto a : numberLine)
          temporaryVec.push_back(a);
        temporaryVec.erase(temporaryVec.begin() + i);

        for (auto a : temporaryVec)
          std::cout << a;
        std::cout << std::endl;

        for (size_t i = 0; i < temporaryVec.size() - 1; ++i) {
          int firstNum = temporaryVec[i];
          int secondNum = temporaryVec[i + 1];
          int difference = abs(firstNum - secondNum);
          if (difference > 0 && difference <= 3 && secondNum >= firstNum) {
            isValid = true;
          } else {
            isValid = false;
            break;
          }
          if (!isValid)
            break;
        }
        if (isValid)
          break;

        if (!isValid) {
          for (size_t i = 0; i < temporaryVec.size() - 1; ++i) {
            int firstNum = temporaryVec[i];
            int secondNum = temporaryVec[i + 1];
            int difference = abs(firstNum - secondNum);
            if (difference > 0 && difference <= 3 && secondNum <= firstNum) {
              isValid = true;
            } else {
              isValid = false;
              break;
            }
            if (!isValid)
              break;
          }
        }
        if (isValid)
          break;
      }
    }
    if (isValid) {
      ++valids;
      for (auto a : numberLine)
        std::cout << a;
      std::cout << " is valid. \n";
    }
  }
  std::cout << valids << std::endl;
  return 0;
}
