// Introduction Example Solved
// Using std::future and std::async()

#include <iostream>
#include <chrono>
#include <future>

int find_answer_how_old_universe_is()
{
	std::cout << "Waiting 5000 milliseconds\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  std::cout << "Returning the age of the universe after 5000 milliseconds\n";
	return 50000000;
}

void do_other_calculations()
{
	std::cout << "Doing other stuff...\n";
  std::cout << "Waiting 1000 milliseconds\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "Other calculations have finished after 1000 milliseconds\n";
}

int main()
{
	std::future<int> the_answer_future = std::async(find_answer_how_old_universe_is);
	do_other_calculations();
	std::cout << "The answer is " << the_answer_future.get() << std::endl;
}