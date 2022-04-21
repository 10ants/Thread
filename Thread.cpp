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

    bool ThreeStatus = false;
    void SetThreeStatus(bool Status) {ThreeStatus = Status;}
    bool GetThreeStatus() {return ThreeStatus;}
    void SetInt(int number) {mNum = number;}
    int GetInt() {return mNum;}
    void SetString(std::string string) {mStr = string; }
    std::string GetString() { return mStr;}
};

void CallFunc(Thing* ThingPTR, int n, std::string s)
{
    ThingPTR->operator()(n, s);
}

void OneCounter(Thing* ThingPTR)
{
    while (!ThingPTR->GetThreeStatus())
    {
        ThingPTR->SetInt(17);
        ThingPTR->SetString("One");
    }
}

void TwoCounter(Thing* ThingPTR)
{
    while (!ThingPTR->GetThreeStatus())
    {
        ThingPTR->SetInt(ThingPTR->GetInt()+13);
        ThingPTR->SetString("Two");
    }
}

void ThreeCounter(Thing* ThingPTR)
{
    int ThreeCount = 0;
    while (ThreeCount != INT_MAX)
    {
        if (ThreeCount == INT_MAX)
            break;
   
        ThingPTR->SetInt(ThreeCount);
        ThingPTR->SetString("Three");
        ThreeCount++;
    }
    ThingPTR->SetThreeStatus(true);
}

int main()
{
    std::cout << "Start\n";
   int RaceTimer = 0;
   while (RaceTimer != 100)
   {
        Thing* ThingPTR = new Thing;
        std::thread WorkerOne(OneCounter, ThingPTR);
        std::thread WorkerTwo(TwoCounter, ThingPTR);
        std::thread WorkerThree(ThreeCounter, ThingPTR);

        while (!ThingPTR->GetThreeStatus())
        {
           std::cout << ThingPTR->GetInt() << " " << ThingPTR->GetString() << std::endl;
           std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        WorkerOne.join();
        WorkerTwo.join();
        WorkerThree.join();
       RaceTimer += 5;
   }
}
