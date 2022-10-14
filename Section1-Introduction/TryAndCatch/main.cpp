#include <iostream>
#include <thread>
#include <chrono>

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
	
  /*
    // Exception from the runtime_error in the function
    other_operations();
    foo_thread.join();
    std::cout << "This is after foo_thread join \n"; 
  */

  try
  {
    other_operations(); 
    foo_thread.join();  // In the try and catch blocks
    std::cout << "This is after foo_thread join \n"; 
  }
  catch(const std::exception& e)
  {
    foo_thread.join();  // In the try and catch blocks
    std::cout << "This is after foo_thread join \n"; 
    std::cerr << e.what() << '\n';
  }
  
	std::cout << "Bye from main thread \n";
}