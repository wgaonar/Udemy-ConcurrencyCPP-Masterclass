#include <iostream>
#include <future>
#include <string>

void printing()
{
	std::cout << "printing runs on id: [" << std::this_thread::get_id() << "]\n";
}

int addition(int x, int y)
{
	std::cout << "addition runs on id: [" << std::this_thread::get_id() << "]\n";
	return x + y;
}

int subtraction(int x, int y)
{
	std::cout << "subtraction runs on id: [" << std::this_thread::get_id() << "]\n";
	return x - y;
}

int main()
{
	std::cout << "main thread runs on this id: [" << std::this_thread::get_id() << "]\n";

	int x = 100;
	int y = 50;

  // async option runs on a separate thread
	std::future<void> f1 = std::async(std::launch::async, printing);

  // deferred option runs on the same creator thread
	std::future<int> f2 = std::async(std::launch::deferred, addition, x, y);

  // deferred | async multiple option lets the choice to the program
	std::future<int> f3 = std::async(std::launch::deferred | std::launch::async,
		                    subtraction, x, y);

	f1.get();
	std::cout << "Value received using f2 (addition) future: " << f2.get() << std::endl;
	std::cout << "Value received using f3 (subtraction) future: " << f3.get() << std::endl;
}