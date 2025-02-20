#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

int main() {
  std::fstream file("./input.txt");
  std::string input;
  int sum = 0;
  std::regex re(R"(mul\((\d+),(\d+)\))"); // Regex to match "mul(3,4)"

  while (std::getline(file, input)) { // Read entire line
    std::sregex_iterator it(input.begin(), input.end(), re);
    std::sregex_iterator end;

    bool found = false;
    for (; it != end; ++it) {
      found = true;
      std::smatch match = *it;
      int a = std::stoi(match[1].str()); // Convert to int
      int b = std::stoi(match[2].str());
      sum += (a * b);

      std::cout << "Matched: " << match.str() << "\n";
      std::cout << "First number: " << a << "\n";
      std::cout << "Second number: " << b << "\n";
    }

    if (!found) {
      std::cout << "No match.\n";
    }
  }

  std::cout << "Sum: " << sum << std::endl;
  return 0;
}
