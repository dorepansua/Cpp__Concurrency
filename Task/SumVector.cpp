#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>

int partial_sum(std::vector<int>::iterator begin,
                std::vector<int>::iterator end) {
  return std::accumulate(begin, end, 0);
}

void doParallel(const std::vector<int> &data, size_t dataSize) {
  auto timeStart = std::chrono::high_resolution_clock::now();
  const size_t numThreads = 12;
  std::vector<std::thread> threads;
  std::vector<std::future<int>> futures;

  size_t blockSize = dataSize / numThreads;
  for (size_t i = 0; i < numThreads; i++) {
    size_t start = i * blockSize;
    size_t end = (i == numThreads - 1) ? dataSize : (i + 1) * blockSize;
    // Step 1: Wrap your work
    std::packaged_task<int(int, int)> sumTask([&](int a, int b) {
      int sum = 0;
      for (size_t j = a; j < b; j++) {
        sum += data[j];
      }
      return sum;
    });

    // Step 2: Create a future
    futures.emplace_back(sumTask.get_future());

    // Step 3: Perform the calculation:
    threads.emplace_back(std::move(sumTask), start, end);
  }

  // step 4:
  // sumResult.get();
  int totalSum = 0;
  for (auto &fut : futures) {
    totalSum += fut.get();
  }

  for (auto &&thread : threads) {
    thread.join();
  }

  auto timeEnd = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart)
          .count();
  std::cout << "   Parallel: Sum by " << numThreads
            << " threads with data size: " << dataSize << " is: " << totalSum
            << " with TIME: " << duration << std::endl;
}

void doNormal(const std::vector<int> &data, size_t dataSize) {
  auto startTime = std::chrono::high_resolution_clock::now();
  int sum = 0;
  for (auto &&value : data) {
    sum += value;
  }

  auto endTime = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime)
          .count();

  std::cout << "   Normal: Sum a vector with size " << dataSize
            << " is: " << sum << " with TIME: " << duration << std::endl;
}

int main() {
  std::cout << "Sum vector by package task\n";
  const size_t dataSize = 50000000;
  std::vector<int> data(dataSize, 1);

  doParallel(data, dataSize);

  doNormal(data, dataSize);

  // Result:
  // Parallel: Sum by 12 threads with data size: 50000000 is: 50000000 with
  // TIME: 62 Normal: Sum a vector with size 50000000 is: 50000000 with TIME: 89

  system("pause");
  return 1;
}