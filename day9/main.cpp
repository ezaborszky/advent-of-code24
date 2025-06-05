#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
const std::uint64_t EMPTY_SENTINEL = UINT64_MAX;

struct FileChunk {
  std::int64_t fileId = 0;
  bool isEmpty = false;
  int fileSize = 0;
  std::string fileIdChar = std::to_string(fileId);
};
std::vector<FileChunk> dataChunks;
void printString(std::vector<std::int64_t> defragVec) {
  for (auto a : defragVec) {
    if (a == -1)
      std::cout << ".";
    if (a != -1)
      std::cout << a;
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  std::fstream file("./input");
  char myChar;
  bool emptySwitch = false;

  std::int64_t fileID = 0;
  while (file >> myChar) {
    if (!emptySwitch) {
      int size = myChar - '0';
      FileChunk chunk{fileID, emptySwitch, size};
      dataChunks.push_back(chunk);
      ++fileID;
    } else if (emptySwitch) {
      int size = myChar - '0';
      FileChunk chunk{-1, emptySwitch, size};
      dataChunks.push_back(chunk);
    }
    emptySwitch = !emptySwitch;
  }

  std::vector<std::int64_t> defragVec;
  std::vector<std::int64_t> onlyFiles;

  for (const auto chunk : dataChunks) {
    if (!chunk.isEmpty) {
      for (size_t i = 0; i < chunk.fileSize; ++i) {
        defragVec.push_back(chunk.fileId);
        onlyFiles.push_back(chunk.fileId);
      }
    } else if (chunk.isEmpty) {
      for (size_t i = 0; i < chunk.fileSize; ++i) {
        defragVec.push_back(-1);
      }
    }
  }
  for (size_t x = 0; x < defragVec.size(); ++x) {
    while (!defragVec.empty() && defragVec.back() == -1)
      defragVec.pop_back();
    if (defragVec[x] == -1) {
      defragVec[x] = defragVec.back();
      defragVec.pop_back();
    }
  }
  std::int64_t sum = 0;

  for (size_t x = 0; x < defragVec.size(); ++x) {
    sum += (x * defragVec[x]);
  }
  std::cout << sum << std::endl;
  return 0;
}
