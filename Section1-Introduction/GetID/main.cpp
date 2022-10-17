#include <iostream>
#include <thread>
#include <chrono>

void func_1()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "This thread id : " << std::this_thread::get_id() << std::endl;
}

int main()
{
	std::thread thread_1(func_1);
	std::thread thread_2(func_1);
	std::thread thread_3(func_1);
	std::thread thread_4;

	std::cout << "Thread_1 id: " << thread_1.get_id() << std::endl;
	std::cout << "Thread_2 id: " << thread_2.get_id() << std::endl;
	std::cout << "Thread_3 id: " << thread_3.get_id() << std::endl;
	std::cout << "Thread_4 id: " << thread_4.get_id() << std::endl;
	
  thread_1.join();
  thread_2.join();
  thread_3.join();

	std::cout << "Main thread id : " << std::this_thread::get_id() << std::endl;

	std::cout << "\nAllowed max number of parallel threads : "
		        << std::thread::hardware_concurrency() << std::endl;
}