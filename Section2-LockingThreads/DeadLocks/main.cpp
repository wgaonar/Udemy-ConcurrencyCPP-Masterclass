#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>

/*********************************************** example 1 ***********************************/
class bank_account 
{
// Friend function to overload insertion operator "<<"
friend std::ostream &operator<<(std::ostream &os, const bank_account &rhs);

private:
  static constexpr const char *def_name = "Unnamed Account";
  static constexpr double def_balance = 0.0;

	double balance;
	std::string name;
	std::mutex m;

public:
  // Delegate constructor which overload the default constructor
	bank_account(double _balance = def_balance, std::string _name = def_name) : balance(_balance), name(_name) {}

  // Don`t let copy constructor
	bank_account(const bank_account& ) = delete;

  // Don`t let assignment operator
	bank_account& operator=(const bank_account&) = delete;

  double get_balance() const
  {
    return balance;
  }

  std::string get_name() const
  {
    return name;
  }

	void withdraw(double amount)
	{
		std::lock_guard<std::mutex> lg(m);
		balance -= amount;
	}

	void deposit(double amount)
	{
		std::lock_guard<std::mutex> lg(m);
		balance += amount;
	}

	void transfer(bank_account& from, bank_account& to, double amount)
	{
		std::lock_guard<std::mutex> lg_1(from.m);
		std::cout << "Lock for " << from.name << " account acquire by " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		std::cout << "Waiting to acquire lock for " << to.name << " account by  " << std::this_thread::get_id() << std::endl;
		std::lock_guard<std::mutex> lg_2(to.m);

		from.balance -= amount;
		to.balance += amount;
		std::cout << "Transfer to - " << to.name << "   from - " << from.name << "  end \n";
	}
};

std::ostream &operator<<(std::ostream &os, const bank_account &rhs)
{
  os << "[ " << rhs.name << " : " << rhs.balance << " ]";
  return os;
}

// The function transfer outside of the class
void transfer(bank_account& from, bank_account& to, double amount)
{
  std::mutex m_1;
  std::lock_guard<std::mutex> lg_1(m_1);
  std::cout << "Lock for " << from.get_name() << " account acquire by " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  std::mutex m_2;
  std::cout << "Waiting to acquire lock for " << to.get_name() << " account by  " << std::this_thread::get_id() << std::endl;
  std::lock_guard<std::mutex> lg_2(m_2);

  from.withdraw(amount);
  to.deposit(amount);
  std::cout << "Transfer to - " << to.get_name() << "   from - " << from.get_name() << "  end \n";
}

void run_code1_1()
{
	bank_account account; // For calling in a thread a local class method
	bank_account account_1(1000, "james");
	bank_account account_2(2000, "Mathew");

	std::thread thread_1(&bank_account::transfer, &account, std::ref(account_1), std::ref(account_2), 500);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::thread thread_2(&bank_account::transfer, &account, std::ref(account_2), std::ref(account_1), 200);

	thread_1.join();
	thread_2.join();
}

void run_code1_2()
{
	bank_account account; // For calling in a thread a local class method
	bank_account account_1(1000, "james");
	bank_account account_2(2000, "Mathew");

  std::cout << account << std::endl;
  std::cout << account_1 << std::endl;
  std::cout << account_2 << std::endl;


	std::thread thread_1(transfer, std::ref(account_1), std::ref(account_2), 500);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::thread thread_2(transfer,std::ref(account_2), std::ref(account_1), 200);

	thread_1.join();
	thread_2.join();
}



/*********************************************** example 2 ***********************************/
std::mutex m1;
std::mutex m2;


void m1_first_m2_second()
{
	std::lock_guard<std::mutex> lg1(m1);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "thread " << std::this_thread::get_id() << " has acquired lock for m1 mutex, its wait for m2 \n";
	std::lock_guard<std::mutex>lg2(m2);
	std::cout << "thread " << std::this_thread::get_id() << " has acquired lock for m2 mutex \n";
}


void m2_first_m1_second()
{
	std::lock_guard<std::mutex> lg1(m2);
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	std::cout << "thread " << std::this_thread::get_id() << " has acquired lock for m2 mutex, its wait for m1 \n";
	std::lock_guard<std::mutex>lg2(m1);
	std::cout << "thread " << std::this_thread::get_id() << " has acquired lock for m1 mutex \n";
}

void run_code2()
{
	std::thread thread_1(m1_first_m2_second);
	std::thread thread_2(m2_first_m1_second);

	thread_1.join();
	thread_2.join();
}


int main()
{
	// run_code1_1();
	run_code1_2();
	// run_code2();

	return 0;
}
