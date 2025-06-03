#include <stdio.h>

#include <condition_variable>
#include <iostream>
#include <latch>
#include <string>
#include <thread>
using namespace std;

std::latch workDone(6);
std::latch goHome(1);
std::mutex count_mutex;

void synchOut(const std::string &s) {
  std::lock_guard<std::mutex> lock(count_mutex);
  std::cout << s << std::endl;
}

class Worker {
 public:
  Worker(const string &_name) : name(_name) {}

  void operator()() {
    synchOut(this->name + "Work done!\n");
    workDone.count_down();
    goHome.wait();

    synchOut(name + ": " + "Good bye!\n");
  }

 private:
  std::string name;
};

int main() {
  std::cout << "\nBOSS: START WORKING! " << '\n';
  Worker herb(" Herb");
  std::jthread t1(herb);

  Worker scott(" Scott");
  std::jthread t2(scott);

  Worker bjarne(" Bjarne");
  std::jthread t3(bjarne);

  Worker andrei(" Andrei");
  std::jthread t4(andrei);

  Worker andrew(" Andrew");
  std::jthread t5(andrew);

  Worker david(" David");
  std::jthread t6(david);

  workDone.wait();

  goHome.count_down();

  std::cout << "BOSS: GO HOME!" << '\n';
  system("pause");
  return 1;
}
