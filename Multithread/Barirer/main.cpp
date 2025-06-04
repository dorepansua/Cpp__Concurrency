#include <barrier>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mut;
std::barrier bar(6);

void synchOut(const std::string &s) {
  std::lock_guard<std::mutex> lock(mut);
  std::cout << s << std::endl;
}

class FullTime {
 public:
  FullTime(const std::string &_name) : name(_name) {}

  void operator()() {
    synchOut(name + "Work done morning \n");
    bar.arrive_and_wait();
    synchOut(name + "Work done afternoon \n");
    bar.arrive_and_wait();
  }

 private:
  std::string name;
};

class PartTime {
 public:
  PartTime(const std::string _name) : name(_name) {}

  void operator()() {
    synchOut(name + "P Work done morning");
    bar.arrive_and_drop();
  }

 private:
  std::string name;
};

int main() {
  std::cout << '\n';

  FullTime herb(" Herb");
  std::jthread herbWork(herb);
  FullTime scott(" Scott");
  std::jthread scottWork(scott);
  FullTime bjarne(" Bjarne");
  std::jthread bjarneWork(bjarne);

  PartTime andrei(" Andrei");
  std::jthread andreiWork(andrei);
  PartTime andrew(" Andrew");
  std::jthread andrewWork(andrew);
  PartTime david(" David");
  std::jthread davidWork(david);

  system("pause");
  return 0;
}