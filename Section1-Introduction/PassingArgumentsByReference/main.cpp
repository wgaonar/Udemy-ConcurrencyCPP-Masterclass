// Passing arguments by reference

#include <iostream>
#include <thread>
#include <chrono>

void func_1(int& x)
{
	while (true)
	{
		std::cout << x << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    x++;
	}
}

int main()
{
  int x = 1;
  std::cout << "Main thread value of x: " << x << std::endl;

  std::thread thread_1(func_1, std::ref(x)); // Note the use of std::ref() to pass arguments by reference
  std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // Sleep the main thread 5000 milliseconds

  x = 100;
  std::cout << "Main thread value of x has changed to: " << x << std::endl;
	thread_1.join();
}