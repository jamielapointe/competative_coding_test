
#include <cassert>
#include <cstdint>
#include <iostream>

using std::cout;

static inline uint32_t count_bits(uint32_t word) {
  uint32_t mask = 1;
  uint32_t count = 0;
  static constexpr uint32_t num_bits{32};
  for (uint32_t i = 0; i < num_bits; ++i) {
    count += word & mask;
    word = word >> 1;
  }
  return count;
}

int main() {
  if (0 == count_bits(0)) {
    cout << "passed";
  } else {
    cout << "failed" << std::endl;
  }
}
