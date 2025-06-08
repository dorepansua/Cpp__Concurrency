#include <future>
#include <iostream>

void factorial(int n, std::promise<int> prom) {
  int result = 1;
  for (int i = 2; i <= n; ++i) result *= i;

  prom.set_value(result);
}

int main() {
  std::cout << "Hung Vu Factorial\n";

  std::promise<int> prom;
  std::future fut = prom.get_future();
  auto futRs = std::async(std::launch::async, factorial, 10, std::move(prom));
  auto rs = fut.get();

  std::cout << "Factorial = " << rs << std::endl;

  futRs.get();
  system("pause");
  return 1;
}
