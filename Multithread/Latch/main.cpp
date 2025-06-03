#include <stdio.h>

#include <condition_variable>
#include <iostream>
#include <thread>
using namespace std;

std::condition_variable cv;
std::mutex mut;
int num = 100;

void Ping() {
  while (num > 0) {
    std::unique_lock<std::mutex> lock(mut);

    cv.wait(lock, []() { return num % 2 == 0; });

    std::cout << "Ping\n";

    num--;

    cv.notify_one();
  }
}

void Pong() {
  while (num > 0) {
    std::unique_lock<std::mutex> lock(mut);

    cv.wait(lock, []() { return num % 2 != 0; });

    std::cout << "Pong\n";

    num--;

    cv.notify_one();
  }
}

int main() {
  printf("Hello World");

  std::jthread t1(Ping);
  std::jthread t2(Pong);

  return 0;
}
