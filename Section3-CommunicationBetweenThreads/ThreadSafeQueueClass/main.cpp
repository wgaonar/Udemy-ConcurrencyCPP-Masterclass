#include <iostream>
#include <mutex>
#include <queue>
#include <memory>
#include <condition_variable>
#include <thread>

template<typename T>
class thread_safe_queue 
{
private:
	std::queue<std::shared_ptr<T>> queue;
	std::mutex m;
	std::condition_variable cv;

public:
  // Default constructor
	thread_safe_queue() {}

  // Copy constructor
	thread_safe_queue(thread_safe_queue const& other_queue)
	{
		std::lock_guard<std::mutex> lg(other_queue.m);
		queue = other_queue.queue;
	}

	void push(T& element)
	{
		std::lock_guard<std::mutex> lg(m);
		queue.push(std::make_shared<T>(element));
		cv.notify_one();
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lg(m);
		if (queue.empty())
		{
			return std::shared_ptr<T>();
		}
    
    std::shared_ptr<T> ref(queue.front());
    queue.pop();
    return ref;
	}

  bool pop(T& ref)
	{
		std::lock_guard<std::mutex> lg(m);
		if (queue.empty())
		{
			return false;
		}

    ref = queue.front();
    queue.pop();
    return true;

	}

	std::shared_ptr<T> wait_pop()
	{
		std::unique_lock<std::mutex> lg(m);
		cv.wait(lg, [this] () { return !queue.empty(); });
		std::shared_ptr<T> ref = queue.front();
		queue.pop();
		return ref;
	}

  bool wait_pop(T& ref)
	{
		std::unique_lock<std::mutex> lg(m);
		cv.wait(lg, [this] {
			return !queue.empty();
			});

		ref = *(queue.front().get());
		queue.pop();
		return true;
	}

	bool empty()
	{
		std::lock_guard<std::mutex> lg(m);
		return queue.empty();
	}

	size_t size()
	{
		std::lock_guard<std::mutex> lg(m);
		return queue.size();
	}
};

thread_safe_queue<int> queue;

void func_1()
{
	int value;
	queue.wait_pop(value);
	std::cout << value << std::endl;
}

void func_2()
{
	int x = 10;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	queue.push(x);
}

int main()
{
	std::thread thread_1(func_1);
	std::thread thread_2(func_2);

	thread_1.join();
	thread_2.join();
}