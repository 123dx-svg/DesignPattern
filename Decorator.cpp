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

//װ���� ת������
class CoffeeDecorator : public Coffee {
public:
	CoffeeDecorator(Coffee* _coffee) :coffee(_coffee) {}
	//���ǵ��ñ�װ�εĶ���ķ���
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

// �Ž��ǡ����������仯ά�ȡ���װ�����ǡ���̬���ӹ��ܡ���
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