// Introduction Example Solved
// Using std::condition_variable and unique_lock<std::mutex>

#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <thread>
#include <chrono>
#include <condition_variable>

bool have_i_arrived = false;
int distance_to_cover = 5;
int distance_covered = 0;
std::condition_variable cv;
std::mutex m;

void keep_driving()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		distance_covered++;
    std::cout << "I am driving, distance covered = " << distance_covered << std::endl;

		// Check the condition variable and notify the waiting 
    // threads if the event occurs
		if (distance_covered == distance_to_cover)
    {
			cv.notify_one();
    }
	}
}

void ask_driver_to_wake_u_up_at_right_time()
{
	std::unique_lock<std::mutex> ul(m);
	cv.wait(ul, [] () {return distance_covered == distance_to_cover; });
	std::cout << "Finally I am there, distance_covered = " << distance_covered << std::endl;
}

int main()
{
  std::cout << "Starting the travel, distance to cover: " << distance_to_cover << std::endl;
  
	std::thread driver_thread(keep_driving);
	std::thread passenger_thread(ask_driver_to_wake_u_up_at_right_time);
	
  passenger_thread.join();
	driver_thread.detach();
}