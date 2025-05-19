

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main() {
  std::fstream file("./input.txt");
  if (!file) {
    std::cerr << "Error: Could not open input.txt\n";
    return 1;
  }

  std::string input;
  std::regex re(
      R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))"); // Match "mul(NUM,NUM)",
                                                 // "do()", and "don't()"

  bool command = true; // Starts enabled
  int sum = 0;

  while (std::getline(file, input)) { // Read each line
    std::sregex_iterator it(input.begin(), input.end(), re);
    std::sregex_iterator end;

    for (; it != end; ++it) {
      std::smatch match = *it;
      std::string found = match.str();

      if (found == "do()") {
        command = true;
      } else if (found == "don't()") {
        command = false;
      } else if (match.size() == 3) { // "mul(NUM,NUM)"
        int a = std::stoi(match[1].str());
        int b = std::stoi(match[2].str());

        if (command) {
          sum += (a * b);
        }
      }
    }
  }

  std::cout << "Final Sum: " << sum << std::endl;
  return 0;
}
