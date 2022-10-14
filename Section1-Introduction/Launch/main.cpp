#include <iostream>
#include <thread>

void func1()
{
	std::cout << "Hello from function - ";
  std::cout << std::this_thread::get_id() << std::endl;
}

class callable_class 
{
public:
	void operator()()
	{
		std::cout << "hello from the class with function call operator - ";
    std::cout << std::this_thread::get_id() << std::endl;
	}
};

int main()
{
	//create thread using fuction
	std::thread thread1(func1);

	//create thread using class with function call operator
	callable_class obj;
	std::thread thread2(obj);

	//create thread using lambda expression
	std::thread thread3([] ()
  {
		std::cout << "hello from the lambda - ";
    std::cout << std::this_thread::get_id() << std::endl;
	});

	thread1.join();
	thread2.join();
	thread3.join();

	std::cout << "This is main thread - ";
  std::cout << std::this_thread::get_id() << std::endl;
}