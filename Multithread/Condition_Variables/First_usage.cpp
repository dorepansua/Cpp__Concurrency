#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::condition_variable cv;
bool dataReady{false};

void doTheWork()
{
    std::cout<<"Process shared data  ..."<<std::endl;
}

void waitingData()
{
    std::cout<<"Waiting data ..."<<std::endl;

    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [](){
        return dataReady;
    });

    doTheWork();

    std::cout<<"Work done! "<<std::endl;

}

void setData()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        dataReady = true;
    }
    std::cout<<" Data is ready"<<std::endl;

    cv.notify_one();
}

int main()
{
    std::cout<<std::endl;

    std::thread t1(waitingData);
    std::thread t2(setData);

    t1.join();
    t2.join();

    system("pause");
    return 1;
}