#include <iostream>
#include <mutex>
#include <stack>
#include <thread>
#include <memory>
#include <stdexcept>

template<typename T>
class thread_safe_stack 
{
private:
	std::stack<std::shared_ptr<T>> stk;
	std::mutex m;

public:
	void push(T element)
	{
		std::lock_guard<std::mutex> lg(m);
		stk.push(std::make_shared<T>(element));
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lg(m);
		if (stk.empty())
		{
			throw std::runtime_error("Stack is empty");
		}

		std::shared_ptr<T> result(stk.top());
		stk.pop();
		return result;
	}

	void pop(T& value)
	{
		std::lock_guard<std::mutex> lg(m);
		if (stk.empty()) 
    {
      throw std::runtime_error("Stack is empty");
    }

		value = *(stk.top().get());
		stk.pop();
	}


	bool empty()
	{
		std::lock_guard<std::mutex> lg(m);
		return stk.empty();
	}

	size_t size()
	{
		std::lock_guard<std::mutex> lg(m);
		return stk.size();
	}
};

// This function displays a stack of T data
// by repeatedly topping and popping the stack
// Note that the stack is passed in by value so we
// don't affect the passed in stack.
template <typename T>
void display(thread_safe_stack<T>& s) 
{
  std::cout << "[ ";
  while (!s.empty()) 
  {
    T elem;
    s.pop(elem);
    std::cout << elem << " ";
  }
  std::cout << "]" << std::endl;
}

int main()
{
  // Instantiate a thread_safe_stack object 
  thread_safe_stack<int> s;
  for (int i: {1,2,3,4,5})
  {
    s.push(i);
  } 

  // Show the list
  display(s);

  // Trying to pop a number when the list is empty
  int number;
  try
  {
    s.pop(number);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    std::cout << "Main program has been terminated!!! \n"; 
  }
  
	return 0;
}