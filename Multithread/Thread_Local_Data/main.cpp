#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <string>

std::mutex mutex;
thread_local std::string string_local("hello from ");

void addThreadLocal(const std::string &s)
{
    string_local +=s;

    std::lock_guard<std::mutex> mut(mutex);
    std::cout<<string_local<<std::endl;
    std::cout<<"&string_local: "<<&string_local<<std::endl;
    std::cout<<std::endl;
}

int main()
{
    std::cout<<std::endl;

    std::thread t1(addThreadLocal, "t1");
    std::thread t2(addThreadLocal, "t2");
    std::thread t3(addThreadLocal, "t3");
    std::thread t4(addThreadLocal, "t4");
    std::thread t5(addThreadLocal, "t5");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    system("pause");
    return 1;
}