#include <iostream>
#include <thread>
#include <chrono>
#include "../../common/common_objs.h"

void foo()
{
	std::cout << "Hello from foo - Waiting 5 seconds \n";
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

	std::thread foo_thread(foo);
	thread_guard tg(foo_thread);  
  
  try
  {
    other_operations();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  // NOTE: The main thread does NOT have to wait for the foo_thread to finish
  // due to the thread_guard object
	std::cout << "Bye from main thread \n";
}