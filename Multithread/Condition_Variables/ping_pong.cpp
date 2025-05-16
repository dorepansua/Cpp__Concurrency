// 1115. Print FooBar Alternately
// Medium
// Topics
// Companies
// Suppose you are given the following code:

// class FooBar {
//   public void foo() {
//     for (int i = 0; i < n; i++) {
//       print("foo");
//     }
//   }

//   public void bar() {
//     for (int i = 0; i < n; i++) {
//       print("bar");
//     }
//   }
// }
// The same instance of FooBar will be passed to two different threads:

// thread A will call foo(), while
// thread B will call bar().
// Modify the given program to output "foobar" n times.

#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <condition_variable>


void printFoo()
{
    std::cout<<"foo"<<std::endl;
}

void printBar()
{
    std::cout<<"bar"<<std::endl;
}

class FooBar {
private:
    int n;

    std::condition_variable cv;
    std::mutex mutex;
    bool isbar{false};
    

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo() {
        
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this](){
                return !this->isbar;
            });

            printFoo();
            isbar = true;
            cv.notify_one();
        }
    }

    void bar() {
        
        for (int i = 0; i < n; i++) {
            
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this](){
                return this->isbar;
            });

            printBar();

            this->isbar = false;
            cv.notify_one();
        }
    }
};


int main()
{
    
    FooBar foobar(20);

    std::thread t1(&FooBar::foo, &foobar);
    std::thread t2(&FooBar::bar, &foobar);


    t1.join();
    t2.join();

    system("pause");
    return 1;
}