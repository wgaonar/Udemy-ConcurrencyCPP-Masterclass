#include <iostream>
#include <thread>
#include <chrono>

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
	
  /*
    // Exception will be launched from the runtime_error 
    in the function: other_operations(). We need to use Try and Catch
  */

  try
  {
    other_operations(); 
    thread_1.join();  // In the try block in case of NO exception
    std::cout << "This is after thread_1 join \n"; 
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << " - Starting to terminate processes...\n";
    thread_1.join();  // In the catch block in case of exception
    std::cout << "Processes has been terminated!!! \n"; 
  }
  
	std::cout << "Bye from main thread \n";
}