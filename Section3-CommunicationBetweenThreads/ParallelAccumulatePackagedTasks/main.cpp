// Parallel Accumulative Algorithm using packaged task objects

#include <iostream>
#include <future>
#include <numeric>
#include <vector>

const int MIN_ELEMENT_COUNT = 1000;

template<typename iterator>
int parallel_accumulate(iterator begin, iterator end)
{
	long length = std::distance(begin, end);

	//at least runs 1000 element
	if (length <= MIN_ELEMENT_COUNT)
	{
		std::cout << std::this_thread::get_id() << std::endl;
		return std::accumulate(begin, end, 0);
	}

	iterator mid = begin;
	std::advance(mid, (length + 1) / 2);

	//Recursive call for the second half of the container data
	std::packaged_task<int(iterator,iterator)> task_1(parallel_accumulate);
  std::future<int> f1 = task_1.get_future();
  task_1(mid, end); // Call the task 1 explicitly
	
  //Recursive call for the first half of the container data
  std::packaged_task<int(iterator,iterator)> task_2(parallel_accumulate);
  std::future<int> f2 = task_2.get_future();
  task_2(begin, mid); // Call the task 2 explicitly

	return f1.get() + f2.get();
}

int main()
{
	std::vector<int> v(4000, 1);
	std::cout << "The sum is " << parallel_accumulate(v.begin(), v.end()) << '\n';
}