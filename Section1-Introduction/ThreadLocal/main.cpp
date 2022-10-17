#include <iostream>
#include <thread>
#include <atomic>


std::atomic<int> i = 0; // Like a global variable shared by all threads
thread_local std::atomic<int> j = 0; // Like a local variable managed by each thread

void foo() 
{
  ++i;
  ++j;
  std::cout << "[atomic variable i: " << i << "] [thread_local variable j: " << j << "]\n";
}

int main() 
{
  std::thread t1(foo);
  std::thread t2(foo);
  std::thread t3(foo);

  t1.join();
  t2.join();
  t3.join();
}