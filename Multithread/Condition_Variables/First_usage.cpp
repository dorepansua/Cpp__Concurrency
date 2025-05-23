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

void setData()
{
   {
        std::unique_lock<std::mutex> lock(mutex);
        dataReady = true;
   }

   std::cout<<"Data is ready..."<<std::endl;
   cv.notify_one();

}


void waitingData()
{
    std::cout<<"Waiting data "<<std::endl;
    std::unique_lock<std::mutex> lock(mutex);


    cv.wait(lock, [](){
        return dataReady;
    });

    //another way to code a wait function.
    // while (![](){
    //     return dataReady;
    // }) {
    //     cv.wait(lock);
    // }

    doTheWork();
    
    std::cout<<"Work done"<<std::endl;
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