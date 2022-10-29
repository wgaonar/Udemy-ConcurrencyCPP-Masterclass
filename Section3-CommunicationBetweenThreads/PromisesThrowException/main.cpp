#include <iostream>       
#include <thread>         
#include <future>         
#include <cmath>         
#include <stdexcept>   

void calculate_square_root(std::promise<int>& prom)
{
	int x = 1;
	std::cout << "Please, enter an integer value: ";
	try
	{
		std::cin >> x;
		if (x < 0)
		{
			throw std::invalid_argument("Input cannot be negative");
		}
		prom.set_value(std::sqrt(x));
	}
	catch (std::exception&)
	{
		prom.set_exception(std::current_exception());
	}
}

void print_result(std::future<int>& fut) {
	try
	{
		int x = fut.get();
		std::cout << "value: " << x << '\n';
	}
	catch (std::exception& e) {
		std::cout << "[exception caught: " << e.what() << "]\n";
	}
}

int main()
{
  // Declare the promise object
	std::promise<int> prom;

  // Assign a future object to the future value of the promise object
	std::future<int> fut = prom.get_future();

  // Start the thread to wait and print the value that will be set in the future
	std::thread printing_thread(print_result, std::ref(fut));

  // Start the thread to set the value
	std::thread calculation_thread(calculate_square_root, std::ref(prom));

	printing_thread.join();
	calculation_thread.join();
}