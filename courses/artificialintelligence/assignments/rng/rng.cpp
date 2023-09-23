#include <iostream>
#include <cstdint>

int main() {
  uint32_t random, S, N;
  int32_t R1, R2;

  std::cin >> random >> N >> R1 >> R2;

  for (int i = 0; i < N; i++)
  {
    random = random xor (random << 13);
    random = random xor (random >> 17);
    random = random xor (random << 5);

    uint32_t value = R1 + (random % (R2 - R1 + 1));

    std::cout << value << std::endl;
  }

  return 0;
}