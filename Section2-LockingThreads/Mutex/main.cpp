#include <iostream>
#include <mutex>
#include <list>
#include <thread>

std::list<int> my_list; // Global to test the mutex lock mechanism
std::mutex m; // Important that it would be global and shared among all threads

// Template function to display any container
template <typename T>
void Display (const T &container)
{
  std::cout << "[ ";
  for(const auto &element : container)
  {
    std::cout << element << " ";
  }
  std::cout << "]\n";
}

void size1()
{
	m.lock();
	int size = my_list.size();
	m.unlock();
	std::cout << "Size of the list is : " << size << "\n\n";
}

void add_to_list1(const int &x)
{
	m.lock();
	my_list.push_back(x);
  Display(my_list);
	m.unlock();
  size1();  // After the m.unlock() because size1() has its own locking mechanisms
}

// The same as size1 but using std::lock_guard<std::mutex>
void size2()
{
	std::lock_guard<std::mutex> lg(m);
	int size = my_list.size();
	std::cout << "Size of the list is : " << size << "\n\n";
}

// The same as add_to_list1 but using std::lock_guard<std::mutex>
void add_to_list2(const int &x)
{
	std::lock_guard<std::mutex> lg(m);
	my_list.push_back(x);
  Display(my_list);
}

int  main()
{
	std::thread thread_1(add_to_list1, 4);

	std::thread thread_2_1(add_to_list2, 11);
  // I have to call the size2() function 
  // in a separate thread because it gives syncronization 
  // error because the implicit behaviour of std::lock_guard()
  std::thread thread_2_2(size2);  

	thread_1.join();
	thread_2_1.join();
	thread_2_2.join();
}