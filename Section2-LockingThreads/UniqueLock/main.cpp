#include <iostream>
#include <mutex>
#include <thread>
#include <string>

void x_operations()
{
	std::cout << "This is X operations \n";
}

void y_operations()
{
	std::cout << "This is Y operations \n";
}

// Make the get_lock function for x_operations
std::unique_lock<std::mutex> get_lock_X()
{
	std::mutex m;
	std::unique_lock<std::mutex> lk(m);
	x_operations();
	return lk;
}

// Make the get_lock function for y_operations
std::unique_lock<std::mutex> get_lock_Y()
{
	std::mutex m;
	std::unique_lock<std::mutex> lk(m);
	y_operations();
	return lk;
}

int main()
{
  // Make the unique_lock for x_operations avoiding a dead lock
	std::unique_lock<std::mutex> lk_x(get_lock_X());

  // Make the unique_lock for y_operations avoiding a dead lock
	std::unique_lock<std::mutex> lk_y(get_lock_Y());

  // Call again the x_operations without problem
	x_operations();

  // Call again the y_operations without problem
	y_operations();

	return 0;
}