// Problems with arguments by reference

#include <iostream>
#include <thread>
#include <chrono>

void func_2(int& x)
{
	while (true)
	{
    try
    {
      std::cout << x << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      x++;
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << " - Starting to terminate processes...\n";
    }
    
	}
}

void func_1()
{
  int x = 0;
  std::thread thread_2(func_2, std::ref(x));
  thread_2.detach(); // Thread_1 exiting without waiting for thread 2

  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  std::cout << "Thread_1 has finished!!! \n";

}

int main()
{
	std::cout << "Hello from main thread \n";
	
  std::thread thread_1(func_1);
  thread_1.join();
  
	std::cout << "Bye from main thread \n";
}