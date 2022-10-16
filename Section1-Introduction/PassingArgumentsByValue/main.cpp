// Passing arguments by value

#include <iostream>
#include <thread>
#include <chrono>

void sum(int x, int y)
{
  std::cout << x << " + " << y << " = " << x + y << std::endl;
}

int main()
{
  int x = 10;
  int y = 20;

  std::thread thread_sum(sum,x, y);
	thread_sum.join();

  return 0;
}