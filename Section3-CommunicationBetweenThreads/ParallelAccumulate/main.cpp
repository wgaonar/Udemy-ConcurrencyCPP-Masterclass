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
	std::future<int> f1 = std::async(std::launch::async,parallel_accumulate<iterator>, mid, end);
	
  // Option 1: Calling directly the function for the first half of the container data
	// auto sum = parallel_accumulate<iterator>(begin, mid);
	// return sum + f1.get();

  // Option 2: Using future for the first half of the container data
  std::future<int> f2 = std::async(std::launch::async,parallel_accumulate<iterator>, begin, mid);
	return f1.get() + f2.get();
}

int main()
{
	std::vector<int> v(4000, 1);
	std::cout << "The sum is " << parallel_accumulate(v.begin(), v.end()) << '\n';
}