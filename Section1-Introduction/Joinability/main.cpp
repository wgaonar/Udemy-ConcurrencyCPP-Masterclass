#include <iostream>
#include <thread>

void func_1()
{
	std::cout << "hello from thread method \n";
}


int main()
{
  std::cout << "Hello from main thread \n";

  // Create the first thread
	std::thread thread_1(func_1);

  // Check if the thread is joinable or not
	if (thread_1.joinable())
	{
		std::cout << "This is joinable thread \n";
	}
	else
	{
		std::cout << "After calling join, thread_1 is not a joinable thread \n";
	}

  // Join the thread
	thread_1.join();

  // Check if the thread is joinable or not
	if (thread_1.joinable())
	{
		std::cout << "This is joinable thread \n";
	}
	else
	{
		std::cout << "After calling join, thread_1 is not a joinable thread \n";
	}

	std::cout << "Bye from main thread \n";
}