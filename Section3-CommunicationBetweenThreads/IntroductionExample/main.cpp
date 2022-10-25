// Introduction Example

#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <thread>
#include <chrono>

bool have_i_arrived = false;
int distance_to_cover = 10;
int distance_covered = 0;

bool keep_driving()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		distance_covered++;
	}

	return false;
}

void keep_awake_all_night()
{
	while (distance_covered < distance_to_cover)
	{
		std::cout << "keep checking, while I am traveling \n";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	std::cout << "Finally I am there, distance_covered = " << distance_covered << std::endl;
}

void set_the_alarm_and_take_a_nap()
{
	if (distance_covered < distance_to_cover)
	{
		std::cout << "Let me take a nap \n";
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	}
	std::cout << "I woke up after a nap, distance_covered = " << distance_covered << std::endl;
}

int main()
{
  std::cout << "Starting the travel, distance to cover: " << distance_to_cover << std::endl;

	std::thread driver_thread(keep_driving);
	std::thread keep_awake_all_night_thread(keep_awake_all_night);
	std::thread set_the_alarm_and_take_a_nap_thread(set_the_alarm_and_take_a_nap);

	set_the_alarm_and_take_a_nap_thread.join();
	keep_awake_all_night_thread.join();
	driver_thread.detach();
}
