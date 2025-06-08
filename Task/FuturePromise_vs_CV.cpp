#include <future>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex printMut;
void printOut(const std::string &message) {
  std::lock_guard<std::mutex> lock(printMut);
  std::cout << message << std::endl;
}

// std::mutex mut;
// std::condition_variable cv;
// bool dataReady{false};
// std::mutex printMut;

// void waitingData()
// {
//     printOut("Waiting data");
//     std::unique_lock lock(mut);
//     cv.wait(lock, [](){
//         return dataReady;
//     });

//     printOut("Waiting data done!");
// }

// void sendData()
// {
//    printOut("Prepare send data...");
//     std::this_thread::sleep_for(std::chrono::milliseconds(500));

//     std::lock_guard<std::mutex> lock(mut);
//     dataReady = true;
//     cv.notify_one();
//     printOut("Prepare send data done");
// }

void waitingData(std::future<void> fut) {
  printOut("Waiting data");
  fut.wait();

  printOut("Waiting data done!");
}

void sendData(std::promise<void> prom) {
  printOut("Prepare send data...");
  prom.set_value();
  printOut("Prepare send data done");
}

int main() {
  // printOut("Enter to send-wait data by CV");
  // std::jthread t1(sendData);
  // std::jthread t2(waitingData);

  printOut("Enter to send-wait data by future and promise");
  std::promise<void> prom;
  std::future<void> fut = prom.get_future();

  std::jthread t1(waitingData, std::move(fut));
  std::jthread t2(sendData, std::move(prom));

  system("pause");
  return 1;
}