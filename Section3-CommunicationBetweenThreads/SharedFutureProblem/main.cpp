#include <iostream>       
#include <thread>         
#include <future>         
#include <stdexcept>   
#include <chrono>
#include <mutex>

void print_result(std::future<int>& fut)
{
	if (fut.valid())
	{
		std::cout << "This is valid future\n";
		std::cout << fut.get() << "\n";
	}
  // To avoid an exception by a thread trying to access 
  // to promise object that belongs to another future object 
	else 
	{
		std::cout << "This is invalid future\n";
	}
}

int main()
{
  // Declare the promise object
	std::promise<int> prom;

  // Assign a future object to the future value of the promise object
	std::future<int> fut(prom.get_future());

  // Start the thread to wait and print the value that will be set in the future
	std::thread th1(print_result, std::ref(fut));

	// Invalid future!!! because th1 keeps the fut object
  std::thread th2(print_result, std::ref(fut)); 

	prom.set_value(5);

	th1.join();
	th2.join();

	return 0;
}
