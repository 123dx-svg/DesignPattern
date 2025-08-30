#include <iostream>
class Coffee {
public:
	virtual float getCost() = 0;
	virtual std::string getDescription() = 0;
};

class SimpleCoffee : public Coffee {
public:
	float getCost() override{
		return 5.0f;
	}
	std::string getDescription() override{
		return "Simple Coffee:";
	}
};

class MilkCoffee : public Coffee {
public:

	float getCost() override {
		return 10.0f;
	}
	std::string getDescription() override {
		return "MilkCoffee:";
	}

};

//装饰器 转发请求
class CoffeeDecorator : public Coffee {
public:
	CoffeeDecorator(Coffee* _coffee) :coffee(_coffee) {}
	//总是调用被装饰的对象的方法
	float getCost() override {
		return coffee->getCost();
	}
	std::string getDescription() override {
		return coffee->getDescription();
	}
private:
	Coffee* coffee;
};

class SugerDecorator : public CoffeeDecorator {
public:
	SugerDecorator(Coffee* _coffee) :CoffeeDecorator(_coffee) {}
	float getCost() override {
		return CoffeeDecorator::getCost() + 2.0f;
	}
	std::string getDescription() override {
		return CoffeeDecorator::getDescription() + " SugerDecaf";
	}
};

class VanillaDecorator : public CoffeeDecorator {
public:
	VanillaDecorator(Coffee* _coffee) :CoffeeDecorator(_coffee) {}
	float getCost() override {
		return CoffeeDecorator::getCost() + 10.0f;
	}
	std::string getDescription() override {
		return CoffeeDecorator::getDescription() + " Vanilla";
	}
};

// 桥接是“解耦两个变化维度”，装饰器是“动态叠加功能”。
int main()
{

	Coffee* coffe = new SimpleCoffee();
	std::cout << coffe->getDescription() << " " << coffe->getCost() << std::endl;

	coffe= new SugerDecorator(coffe);
	std::cout << coffe->getDescription() << " " << coffe->getCost() << std::endl;

	coffe = new VanillaDecorator(coffe);
	std::cout << coffe->getDescription() << " " << coffe->getCost() << std::endl;
	

	return 0;

}