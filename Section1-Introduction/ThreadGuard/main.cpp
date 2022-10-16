#include <iostream>
#include <thread>
#include <chrono>
#include "../../common/common_objs.h"

void func_1()
{
	std::cout << "Hello from func_1 - Waiting 5 seconds \n";
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void other_operations()
{
	std::cout << "This is other operation \n";

  // Launch a deliberate exception!!! 
  throw std::runtime_error("This is a runtime error");
}


int main()
{
	std::cout << "Hello from main thread \n";

	std::thread thread_1(func_1);
	thread_guard tg(thread_1);  
  
  try
  {
    other_operations();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  // NOTE: The main thread does NOT have to wait for the thread_1 to finish
  // due to the thread_guard object
	std::cout << "Bye from main thread \n";
}