#include <iostream>
#include <future>
#include <chrono>
#include <thread>

int slowFunction()
{
    std::this_thread::sleep_for(std::chrono::seconds(6));
    return 42;
}


int main()
{
    std::future<int> future = std::async(std::launch::async, slowFunction);

    while (future.wait_for(std::chrono::milliseconds(500)) != std::future_status::ready) {

        //time out or deffer
        std::cout<<"Task is still running..."<<std::endl;
    
    }

    int result = future.get();
    std::cout<<"Task completed with result: "<<result<<std::endl;
    return 1;
}