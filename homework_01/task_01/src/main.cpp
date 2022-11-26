#include <iostream>

#include "utils.hpp"
int main() {
  std::cout << SplitString("aaa aaa ").size() << std::endl;
  for (const auto &word : SplitString("aaa aaa ")) {
    std::cout << word << "\n";
  }
  return 0;
}
