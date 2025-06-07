#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
const std::uint64_t EMPTY_SENTINEL = UINT64_MAX;

struct FileChunk {
  std::int64_t fileId = 0;
  bool isEmpty = false;
  int fileSize = 0;
  std::string fileIdChar = std::to_string(fileId);
  bool isChecked = false;
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

  for (auto rit = dataChunks.rbegin(); rit != dataChunks.rend(); ++rit) {
    if (!rit->isEmpty && !rit->isChecked) {
      for (auto it = dataChunks.begin(); it < rit.base(); ++it) {
        if (it->isEmpty && it->fileSize >= rit->fileSize) {
          int sizeDif = it->fileSize - rit->fileSize;
          FileChunk replacementEmpty{-1, true, rit->fileSize, "-1", false};
          FileChunk extraSpace{-1, true, sizeDif, "-1", false};
          *it = *rit;
          *rit = replacementEmpty;
          auto tempRit = rit.base();
          if (sizeDif)
            dataChunks.insert(it + 1, extraSpace);
          rit = std::reverse_iterator(tempRit);
          break;
        }
      }
    }
  }

  for (auto a : dataChunks) {
    for (size_t x = 0; x < a.fileSize; ++x) {
      defragVec.push_back(a.fileId);
    }
  }

  std::int64_t sum = 0;

  for (size_t x = 0; x < defragVec.size(); ++x) {
    if (defragVec[x] > -1)
      sum += (x * defragVec[x]);
  }
  std::cout << sum << std::endl;
  return 0;
}
