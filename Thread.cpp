#include <iostream>
#include <string>
#include <thread>
#include <Windows.h>

class Thing																								  
{											
	std::string mStr = " ";
	int mNum = 0;

public:
	Thing(int num, std::string string)
	{
		mNum = num;
		mStr = string;
	}
	~Thing(){}

	struct Functor
	{
		void operator()(Thing* ThingPTR, int count ,std::string ID)
		{
			ThingPTR->SetInt(+count);
			ThingPTR->SetString(ID);
		}
	};

	void SetInt(int number) {mNum = number;}
	int GetInt() {return mNum;}
	void SetString(std::string string) {mStr = string;}
	std::string GetString() {return mStr;}
	
};

int main()
{
	std::cout << "Start\n";
	int times = 0; //Used to prevent infinite loop

	while (times < 50)
	{
		std::thread WorkerOne;
		std::thread WorkerTwo;
		std::thread WorkerThree;
		int ThreeCount = 0;
		
		Thing* ThingPTR = new Thing(0, " ");
		Thing::Functor()(ThingPTR, 17, "one");

		std::thread WorkerOne(Thing::Functor()(ThingPTR, 17, "one"));
		std::this_thread::yield();
		std::thread WorkerTwo(Thing::Functor()(ThingPTR, 13, "two"));
		std::this_thread::yield();
		std::thread WorkerThree(Thing::Functor()(ThingPTR, ThreeCount, "three"));
		std::this_thread::yield();

		for (int i = 0; i < INT_MAX; i++)
		{
			ThreeCount = i;
		}
		times += 1;
		Sleep(1);

		std::cout << "Current int value is...." << ThingPTR->GetInt() << std::endl;
		std::cout << "This was set by thread...." << ThingPTR->GetString() << std::endl;
	}

	std::cout << "End\n";
}
