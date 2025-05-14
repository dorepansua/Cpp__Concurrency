
#include <iostream>
#include <atomic>
#include <stdlib.h>
#include <thread>

class SpinLock
{
    std::atomic_flag m_flag = ATOMIC_FLAG_INIT; 

public:
    SpinLock() {}


    void lock()
    {
        while (!m_flag.test_and_set(std::memory_order_acquire)) {
            std::cout<<"Pending..."<<std::endl;
        }
    }

    void unlock()
    {
        m_flag.clear(std::memory_order_release);
    }
};


SpinLock spinLock;


int global_count = 0;

void DoSomeThing()
{
    spinLock.lock();
    for (int i = 0; i < 100000 ; ++i) {
        global_count++;
    }
    spinLock.unlock();
}

int main()
{
    std::thread t1(DoSomeThing);
    std::thread t2(DoSomeThing);



    t1.join();
    t2.join();


    std::cout<<"global_count = "<<global_count;

    system("pause");
    return 0;
}
