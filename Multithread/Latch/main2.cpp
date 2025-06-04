#include <iostream>
#include <latch>
#include <thread>

std::latch lat(3);
void printOutput(const std::string &message) {
  std::cout << message << std::endl;
}

class Worker {
 public:
  Worker(const std::string &name) : name(name) {}

  void operator()() {
    printOutput(name + ": " + "Work done!\n");

    lat.arrive_and_wait();

    printOutput(name + ": " + "See you tomorrow!\n");
  }

 private:
  std::string name;
};

int main() {
  std::cout << "Begin working\n";

  Worker herb("herb");
  std::jthread t1(herb);

  Worker hung("hung");
  std::jthread t2(hung);

  Worker zu("zu");
  std::jthread t3(zu);

  system("pause");
  return 1;
}
