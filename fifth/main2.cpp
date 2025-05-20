#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>

int isXmas(std::vector<std::string> text) {
  int sum = 0;
  for (size_t row = 0; row < text.size(); ++row) {
    for (size_t col = 0; col < text[row].size(); ++col) {

      bool isXmas = true;
      std::string temp = "";
      char curChar = text[row][col];
      if (curChar == 'A' && row >= 1 && row + 1 < text.size() && col >= 1 &&
          col + 1 < text[row].size()) {
        char upperLeft = text[row - 1][col - 1];
        char lowerLeft = text[row + 1][col - 1];
        char upperRight = text[row - 1][col + 1];
        char lowerRight = text[row + 1][col + 1];

        if ((upperLeft == 'M' && lowerRight == 'S') ||
            (upperLeft == 'S' && lowerRight == 'M')) {
          if ((upperRight == 'M' && lowerLeft == 'S') ||
              (upperRight == 'S' && lowerLeft == 'M')) {
            ++sum;
          }
        }
      }
    }
  }

  return sum;
}

int main(int argc, char *argv[]) {
  std::fstream file("./input");
  std::string line = "";
  std::vector<std::string> alllines = {};

  while (std::getline(file, line)) {
    alllines.push_back(line);
  }
  int sum = 0;

  sum = isXmas(alllines);
  std::cout << sum << "\n";

  return 0;
}
