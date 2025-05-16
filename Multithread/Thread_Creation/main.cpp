#include <iostream>
#include <thread>

//function
void thread_run()
{
    std::cout<<"Thread run"<<std::endl;
}

//object
class ThreadObject
{
    public:
    ThreadObject()
    {
        std::cout<<"ThreadObject contructor()"<<std::endl;
    }

    void operator()(){
        std::cout<<"ThreadObject operator () "<<std::endl;
    }

};


int main()
{
    std::cout<<"Start main"<<std::endl;
    std::thread t1(thread_run);


    ThreadObject object;
    std::thread t2(object);

    std::thread t3([](){
        std::cout<<"Thead run by lambda"<<std::endl;
    });

    t2.join();
    t1.join();
    t3.join();

    system("pause");
    return 1;
}