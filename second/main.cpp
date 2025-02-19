#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int agrc, char *argv[]) {

  std::vector<int> firstCol = {};
  std::vector<int> secondCol = {};
  int difference = 0;
  int index = 1;

  std::fstream file("./input.md");
  std::string text = "";
  int chunk = 1;
  while (file >> chunk) {

    if (index % 2 != 0)
      firstCol.push_back(chunk);
    if (index % 2 == 0)
      secondCol.push_back(chunk);
    ++index;
  }

  std::sort(firstCol.begin(), firstCol.end());
  std::sort(secondCol.begin(), secondCol.end());

  for (size_t i = 0; i < firstCol.size(); ++i) {
    int counter = 0;
    for (auto num : secondCol) {
      if (firstCol[i] == num)
        ++counter;
      //  std::cout << "blip \n";
    }
    difference += firstCol[i] * counter;
  }

  std::cout << difference << std::endl;

  return 0;
}
