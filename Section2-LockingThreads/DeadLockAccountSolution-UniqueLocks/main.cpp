#include <iostream>
#include <mutex>
#include <thread>
#include <string>


/***************************************************Example 1 ******************************************/
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
		balance += amount;
	}

	void deposit(double amount)
	{
		std::lock_guard<std::mutex> lg(m);
		balance += amount;
	}

	void transfer(bank_account& from, bank_account& to, double amount)
	{
		std::cout << "The Thread: " << std::this_thread::get_id() << " Hold the lock for both mutex \n";

    // Using unique_lock and std::defer_lock to avoid the dead lock problem
		std::unique_lock<std::mutex> ul_1(from.m, std::defer_lock);
		std::unique_lock<std::mutex> ul_2(to.m, std::defer_lock);
		std::lock(ul_1, ul_2);

		from.balance -= amount;
		to.balance += amount;
		std::cout << "Transfer to - " << to.name << "   from - " << from.name << "  end \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
};

std::ostream &operator<<(std::ostream &os, const bank_account &rhs)
{
  os << "[ " << rhs.name << " : " << rhs.balance << " ]";
  return os;
}

int main()
{
	bank_account account;
	bank_account account_1(1000, "James");
	bank_account account_2(2000, "Mathew");

  // Balance before the transfer
  std::cout << account << std::endl;
  std::cout << account_1 << std::endl;
  std::cout << account_2 << std::endl;

	std::thread thread_1(&bank_account::transfer, &account, std::ref(account_1), std::ref(account_2), 500);
	std::thread thread_2(&bank_account::transfer, &account, std::ref(account_2), std::ref(account_1), 200);

	thread_1.join();
	thread_2.join();

  // Balance after the transfer
  std::cout << account_1 << std::endl;
  std::cout << account_2 << std::endl;

	return 0;
}