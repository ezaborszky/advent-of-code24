#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int isXmas(std::vector<std::string> text) {
  int sum = 0;
  for (size_t row = 0; row < text.size(); ++row) {
    for (size_t col = 0; col < text[row].size(); ++col) {

      bool isXmas = true;
      std::string temp = "";

      // HORIZONTAL
      if (col + 3 <= text[row].size()) {
        temp.push_back(text[row][col]);
        temp.push_back(text[row][col + 1]);
        temp.push_back(text[row][col + 2]);
        temp.push_back(text[row][col + 3]);

        if (temp == "XMAS" || temp == "SAMX")
          ++sum;
        temp = "";
      }

      // VERTICAL
      if (row + 3 < text.size()) {
        temp.push_back(text[row][col]);
        temp.push_back(text[row + 1][col]);
        temp.push_back(text[row + 2][col]);
        temp.push_back(text[row + 3][col]);

        if (temp == "XMAS" || temp == "SAMX")
          ++sum;
        temp = "";
      }

      // DIAGONAL RIGHT
      if (row + 3 < text.size() && col + 3 <= text[row].size()) {
        temp.push_back(text[row][col]);
        temp.push_back(text[row + 1][col + 1]);
        temp.push_back(text[row + 2][col + 2]);
        temp.push_back(text[row + 3][col + 3]);

        if (temp == "XMAS" || temp == "SAMX")
          ++sum;
        temp = "";
      }

      // DIAGONAL LEFT
      if (row + 3 < text.size() && col >= 3) {
        temp.push_back(text[row][col]);
        temp.push_back(text[row + 1][col - 1]);
        temp.push_back(text[row + 2][col - 2]);
        temp.push_back(text[row + 3][col - 3]);

        if (temp == "XMAS" || temp == "SAMX")
          ++sum;
        temp = "";
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
