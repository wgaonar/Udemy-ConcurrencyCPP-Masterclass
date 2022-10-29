#include <iostream>       
#include <thread>         
#include <future>         
#include <stdexcept>   
#include <chrono>
#include <mutex>

void print_result(std::shared_future<int>& fut)
{
	std::cout << fut.get() << "  - valid future \n";
}

int main()
{
  // Declare the promise object
	std::promise<int> prom;

  // Assign a shared_future object to the future value of the promise object
	std::shared_future<int> fut(prom.get_future());

  // Start the first thread that shares the promise object
	std::thread th1(print_result, std::ref(fut));

  // Start the second thread that shares the promise object
	std::thread th2(print_result, std::ref(fut));

	prom.set_value(5);

	th1.join();
	th2.join();

	return 0;
}
