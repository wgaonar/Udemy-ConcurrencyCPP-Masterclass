#include <iostream>       
#include <functional>     
#include <thread>        
#include <future>       
#include <stdexcept>

void print_int(std::future<int>& fut) 
{
	std::cout << "Waiting for value in the print thread \n";
	std::cout << "Value was set to: " << fut.get() << "\n";
}

int main()
{
  // Declare the promise object
	std::promise<int> prom;

  // Assign a future object to the future value of the promise object
	std::future<int> fut = prom.get_future();

  // Start the thread to wait and print the value that will be set in the future
	std::thread print_thread(print_int, std::ref(fut));

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	std::cout << "Set the value in main thread \n";
	prom.set_value(10);

  // Finish the call to the function in the thread and the thread itself
	print_thread.join();
}