#include <iostream>
#include <string>
#include <vector>

//��Ʒ
class Item {
private:
    std::string name;
    int price;
public:
    Item(std::string name, int price) : name(name), price(price) {}
    std::string getName() const { return name; }
    int getPrice() const { return price; }
};

class PaymentStrategy {
public:
    virtual void pay(double amount) = 0;
};

class CreditCardStrategy : public PaymentStrategy {
private:
    std::string cardNumber;
public:
    CreditCardStrategy(std::string cardNumber) : cardNumber(cardNumber) {}
    void pay(double amount) override {
        std::cout << "Paying " << amount << " using credit card " << cardNumber << std::endl;
    }
};

class PaypalStrategy : public PaymentStrategy {
private:
    std::string email;
public:
    PaypalStrategy(std::string email) : email(email) {}
    void pay(double amount) override {
        std::cout << "Paying " << amount << " using Paypal account " << email << std::endl;
    }
 };

 class BitcoinStrategy : public PaymentStrategy {
 private:
    std::string address;
public:
    BitcoinStrategy(std::string address) : address(address) {}
    void pay(double amount) override {
        std::cout << "Paying " << amount << " using Bitcoin address " << address << std::endl;
    }
 };

 //���ﳵ
class ShoppingCart {
private:
    std::vector<Item*> items;

public:
   ShoppingCart(){}

   void addItem(Item* item) {
       items.push_back(item);
   }

   void removeItem(Item* item) {
       items.erase(std::remove(items.begin(), items.end(), item), items.end());
   }

   int calculateTotal() const {
       int total = 0;
       for (auto item : items) {
           total += (*item).getPrice();
       }
       return total;
   }

   void pay(PaymentStrategy* strategy) {
       int amount = calculateTotal();
       strategy->pay(amount);
   }
};

//���㷨������װ
/*
����ģʽ�ǣ������뻻����ʽ������¡�

����֧����ʽ���������㷨��
�н���ģʽ�ǣ������Ǳ����绰�ˣ��������ҡ�*/
int main()
{
    ShoppingCart* cart = new ShoppingCart();

	cart->addItem(new Item("book", 10));
	cart->addItem(new Item("pen", 5));
	cart->addItem(new Item("chair", 20));

    cart->pay(new CreditCardStrategy("1234567890"));
    cart->pay(new PaypalStrategy("john.doe@gmail.com"));
    cart->pay(new BitcoinStrategy("1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa"));





return 0;

}