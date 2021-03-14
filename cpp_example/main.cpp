#include <functional>
#include <iostream>

int main(int argc, char const *argv[]) {
  auto h = std::hash<int>();

  std::cout << h(0) << '\n';

  return 0;
}
