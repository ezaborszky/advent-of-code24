#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

const int HEIGHT = 103;
const int WIDTH = 101;
const int TIME = 100;

struct pair_hash {
  std::size_t operator()(const std::pair<int, int> &p) const {
    return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
  }
};

std::unordered_map<std::pair<int, int>, int, pair_hash> frequencyMap;

class Roboter {
public:
  Roboter(std::pair<int, int> location, std::pair<int, int> velocity);
  std::pair<int, int> location;
  std::pair<int, int> velocity;
  void updateLocation();
};

Roboter::Roboter(std::pair<int, int> location, std::pair<int, int> velocity)
    : location(location), velocity(velocity) {};

void Roboter::updateLocation() {

  location.first = ((location.first + velocity.first) % WIDTH + WIDTH) % WIDTH;
  location.second =
      ((location.second + velocity.second) % HEIGHT + HEIGHT) % HEIGHT;
}

Roboter tokenizer(std::string input) {
  int px, py, vx, vy;
  std::string token;
  std::stringstream stream(input);
  std::getline(stream, token, '=');
  std::getline(stream, token, ',');
  px = std::stoi(token);
  std::getline(stream, token, ' ');
  py = std::stoi(token);
  std::getline(stream, token, '=');
  std::getline(stream, token, ',');
  vx = std::stoi(token);
  std::getline(stream, token);
  vy = std::stoi(token);
  Roboter newRoboter({px, py}, {vx, vy});
  return newRoboter;
}

int main(int argc, char *argv[]) {
  std::fstream file("./input");
  std::string input;
  std::vector<Roboter> robots;
  while (std::getline(file, input)) {
    auto newRoboter = tokenizer(input);
    robots.push_back(newRoboter);
  }

  std::vector<std::pair<int, float>> averages;

  std::unordered_map<std::pair<int, int>, int, pair_hash> frequencyMap;
  int max = 0;
  for (int i = 0; i < 10000; ++i) {

    frequencyMap.clear();
    for (auto &a : robots) {
      a.updateLocation();

      ++frequencyMap[{a.location}];
    }
    int botsInBox = 0;
    for (const auto &[key, value] : frequencyMap) {
      if (key.first > 25 && key.first < 75 && key.second > 25 &&
          key.second < 75) {
        botsInBox += value;
      }
    }
    averages.emplace_back(i + 1, botsInBox / robots.size());
    float avg = float((float(botsInBox) / robots.size()) * 100);
    if (avg > 70) {

      for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
          if (frequencyMap[{x, y}] > 0) {
            std::cout << "*";
          } else {
            std::cout << " ";
          }
        }
        std::cout << "\n";
      }
    }
  }

  std::cout << max + 1 << "\n";
  // int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
  //
  // for (int y = 0; y < HEIGHT / 2; ++y) {
  //   for (int x = 0; x < WIDTH / 2; ++x) {
  //     q1 += frequencyMap[{x, y}];
  //   }
  // }
  //
  // for (int y = 0; y < HEIGHT / 2; ++y) {
  //   for (int x = (WIDTH / 2) + 1; x < WIDTH; ++x) {
  //     q2 += frequencyMap[{x, y}];
  //   }
  // }
  //
  // for (int y = (HEIGHT / 2) + 1; y < HEIGHT; ++y) {
  //   for (int x = 0; x < WIDTH / 2; ++x) {
  //     q3 += frequencyMap[{x, y}];
  //   }
  // }
  //
  // for (int y = (HEIGHT / 2) + 1; y < HEIGHT; ++y) {
  //   for (int x = (WIDTH / 2) + 1; x < WIDTH; ++x) {
  //     q4 += frequencyMap[{x, y}];
  //   }
  // }
  //
  // int safetyFactor = q1 * q2 * q3 * q4;
  // std::cout << safetyFactor << std::endl;
  return 0;
}
