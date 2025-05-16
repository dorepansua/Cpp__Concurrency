#include <iostream>
#include <stdlib.h>
#include <utility>

class MySingleton
{
    public:
    static MySingleton& getInstance()
    {
        static MySingleton instance;
        return instance;
    }

    void doSomething()
    {
        std::cout<<"Call a function from singleton\n";
    }

    private:
    MySingleton() = default;
    ~MySingleton() = default;

    MySingleton (const MySingleton& ) = delete;
    MySingleton& operator=(const MySingleton&) = default;
};

int main()
{
    auto& singleton = MySingleton::getInstance();
    singleton.doSomething();
    system("pause");
    return 1;
}