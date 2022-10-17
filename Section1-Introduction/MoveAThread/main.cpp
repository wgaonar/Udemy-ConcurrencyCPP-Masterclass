#include <iostream>
#include <thread>

void func_1()
{
	std::cout << "This is a function 1 \n";
}

void func_2()
{
	std::cout << "This is a function 2 \n";
}

int main()
{
	std::thread thread_1(func_1);

	//std::thread thread_2 = thread_1;  Compiler ERROR!!!

	//Move one thread form another
	std::thread thread_2 = std::move(thread_1);

	//It is valid to call the implicit move constructor with a TEMPORARY thread object at rhs
	thread_1 = std::thread(func_2);

	std::thread thread_3 = std::move(thread_2);

	// thread_1 = std::move(thread_3);  // Execution ERROR because thread_1 did not own any NAME VARIABLE thread object

	thread_1.join();  // It has a TEMPORARY thread object
	// thread_2.join();  // It is not available since It was moved to thread_3
	thread_3.join();

}