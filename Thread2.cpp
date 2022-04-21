#include <iostream>
#include <string>
#include <thread>
#include <Windows.h>

class Thing
{
    std::string mStr = " ";
    int mNum = 0;

public:

    void operator()(int n, std::string s) //Functor
    {
        this->mNum = n;
        this->mStr = s;
    }

    bool Timer = false;
    void SetInt(int number) {mNum = number;}
    int GetInt() {return mNum;}
    void SetString(std::string string) {mStr = string; }
    std::string GetString() { return mStr;}
};


struct OneCounter
{
    Thing* mPTR = nullptr;
    void operator()()
    {
        while (mPTR->Timer != true)
        {
            mPTR->SetInt(17);
            mPTR->SetString("One");
        }
    }
};

struct TwoCounter
{
    Thing* mPTR = nullptr;
    void operator()()
    {
        while (mPTR->Timer != true)
        {
            mPTR->SetInt(mPTR->GetInt() + 13);
            mPTR->SetString("Two");
        }
    }
};

struct ThreeCounter
{
    Thing* mPTR = nullptr;
    void operator ()()
    {
        int ThreeCount = 0;
        while (ThreeCount != INT_MAX)
        {
            if (mPTR->Timer == true)
                break;

            mPTR->SetInt(ThreeCount);
            mPTR->SetString("Three");
            ThreeCount++;
        }
 
    }
};

int main()
{
    Thing* ThingPTR = new Thing;
    OneCounter one;
    one.mPTR = ThingPTR;
    TwoCounter two;
    two.mPTR = ThingPTR;
    ThreeCounter three;
    three.mPTR = ThingPTR;

    std::cout << "Start\n";;
    std::thread WorkerOne(one);
    std::thread WorkerTwo(two);
    std::thread WorkerThree(three);
    int RaceTimer = 0;
        while (RaceTimer <= 100)
        {
           std::cout << ThingPTR->GetInt() << " " << ThingPTR->GetString() << std::endl;
           std::this_thread::sleep_for(std::chrono::seconds(1));
           RaceTimer += 1;
        }
        ThingPTR->Timer = true;

        WorkerOne.join();
        WorkerTwo.join();
        WorkerThree.join();
       
}
