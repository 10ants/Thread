#include <iostream>
#include <string>
#include <thread>
//#include <Windows.h>

class Thing
{
    std::string mStr = " ";
    int mNum = 0;

public:

    void operator()(int n, std::string s) //Functor
    {
        this->mNum  =n;
        this->mStr = s;
    }

    void SetInt(int number) {mNum = number;}
    int GetInt() {return mNum;}
    void SetString(std::string string) {mStr = string;}
    std::string GetString() {return mStr;}
    
};

void CallFunc(Thing* ThingPTR, int n, std::string s)
{
    ThingPTR->operator()(n, s);
}
int main()
{
    std::cout << "Start\n";
    int ThreeCount = 0;

    while (ThreeCount < INT_MAX)
    {
        int ThreeCount = 0;
        
        Thing* ThingPTR = new Thing;
        
        std::thread WorkerOne(CallFunc, ThingPTR, 17, "One");
        std::this_thread::yield();
        std::thread WorkerTwo(CallFunc, ThingPTR, 16, "Two");
        std::this_thread::yield();
        std::thread WorkerThree(CallFunc, ThingPTR, ThreeCount, "Three");
        std::this_thread::yield();

        for (int i = 0; i < INT_MAX; i++)
        {
            ThreeCount = i;
        }
        
        //Sleep(1);
        std::cout << "Current int value is...." << ThingPTR->GetInt() << std::endl;
        std::cout << "This was set by thread...." << ThingPTR->GetString() << std::endl;
        std::cout << "End"<<std::endl;
    }
}
