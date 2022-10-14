#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
	std::cout << "Hello from foo - Waiting 5 seconds \n";
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void bar()
{
	std::cout << "Hello from bar - Waiting 5 seconds \n";
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}


int main()
{
	std::cout << "Hello from main thread \n";

	std::thread foo_thread(foo);
	std::thread bar_thread(bar);

  bar_thread.detach();
  std::cout << "This is after bar_thread detach \n";

	foo_thread.join();
  std::cout << "This is after foo_thread join \n";
	
	std::cout << "Bye from main thread \n";
}