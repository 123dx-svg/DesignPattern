#include <iostream>


class Account {
public:


	virtual std::string getClassName()  = 0;

	void setNext(Account* account) {
		next = account;
	}

	void pay(double amount) {
		if (canPay(amount))
		{
			std::cout << "Paid " << amount << " using " << getClassName() << std::endl;
		}else if (next!= nullptr)
		{
			std::cout << "Cannot pay " << amount << " using " << getClassName() << std::endl;
			next->pay(amount);
		}else
		{
			std::cout << "Cannot pay " << amount << std::endl;
		}
		
	}

	bool canPay(double amount)
	{
		return this->balance >= amount;
	}

protected:	
	Account* next;
	double balance;
	std::string className;
};


class BankAccount : public Account {
public:
	BankAccount(double balance) : Account() {
		this->balance = balance;
		this->className = "Bank Account";
	}
	std::string getClassName() override {
		return this->className;
	}
};

class PaypalAccount : public Account {
public:
	PaypalAccount(double balance) : Account() {
		this->balance = balance;
		this->className = "Paypal Account";
	}
	std::string getClassName() override {
		return this->className;
	}
};
class BitcoinAccount : public Account {
public:
	BitcoinAccount(double balance) : Account() {
		this->balance = balance;
		this->className = "Bitcoin Account";
	}
	std::string getClassName() override {
		return this->className;
	}
};


//解耦请求与处理者 不要和链表结构混淆 这个是带条件的   
//事件处理、技能释放、UI点击冒泡等 都可以用责任链模式
int main()
{
	BankAccount* bank = new BankAccount(100);
	PaypalAccount* paypal = new PaypalAccount(200);
	BitcoinAccount* bitcoin = new BitcoinAccount(300);

	bank->setNext(paypal);
	paypal->setNext(bitcoin);

	bank->pay(250);

	return 0;

}