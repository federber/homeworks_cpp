#include <iostream>

#include "utils.hpp"

int main() {
  std::string data;
  std::getline(std::cin, data);
  std::cout << Calculate("") << std::endl;
  return 0;
}
