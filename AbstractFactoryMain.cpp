#include <iostream>

class IDoor
{
public:
	virtual void Open() = 0;

	virtual ~IDoor()
	{
		std::cout << "IDoor destroyed" << std::endl;
	}
};

class ADoor : public IDoor
{
public:
	ADoor()
	{
		std::cout << "ADoor created" << std::endl;
	}
	void Open() override
	{
		std::cout << "ADoor opened" << std::endl;
	}
	~ADoor()
	{
		std::cout << "ADoor destroyed" << std::endl;
	}
};

class BDoor : public IDoor
{
public:
	BDoor()
	{
		std::cout << "BDoor created" << std::endl;
	}
	
	void Open() override
	{
		std::cout << "BDoor opened" << std::endl;
	}
	~BDoor()
	{
		std::cout << "BDoor destroyed" << std::endl;
	}
};
class IWorker
{
public:
	virtual void Work() = 0;
	virtual ~IWorker()
	{
		std::cout << "IWorker destroyed" << std::endl;
	}
};
class AWorker : public IWorker
{
public:
	AWorker()
	{
		std::cout << "AWorker created" << std::endl;
	}
	void Work() override
	{
		std::cout << "AWorker working" << std::endl;
	}
	~AWorker()
	{
		std::cout << "AWorker destroyed" << std::endl;
	}
};
class BWorker : public IWorker
{
public:
	BWorker()
	{
		std::cout << "BWorker created" << std::endl;
	}
	void Work() override
	{
		std::cout << "BWorker working" << std::endl;
	}
	~BWorker()
	{
		std::cout << "BWorker destroyed" << std::endl;
	}
};


class IDoorFactory
{
public:

	virtual std::unique_ptr<IDoor> MakeDoor() = 0;
	virtual std::unique_ptr<IWorker> MakeWorker() = 0;

	virtual ~IDoorFactory()
	{
		std::cout << "IDoorFactory destroyed" << std::endl;
	}	
	
};

class AFactory : public IDoorFactory
{
public:
	std::unique_ptr<IDoor> MakeDoor()
	{
		return std::make_unique<ADoor>();
	}
	std::unique_ptr<IWorker> MakeWorker()
	{
		return std::make_unique<AWorker>();
	}

	~AFactory()
	{
		std::cout << "AFactory destroyed" << std::endl;
	}
};
class BFactory : public IDoorFactory
{
public:
	std::unique_ptr<IDoor> MakeDoor()
	{
		return std::make_unique<BDoor>();
	}
	std::unique_ptr<IWorker> MakeWorker()
	{
		return std::make_unique<BWorker>();
	}

	~BFactory()
	{
		std::cout << "BFactory destroyed" << std::endl;	
	}
};


//通过工厂创建一系列相关对象，客户端通过接口与对象创建过程解耦
int main()
{

	//注意门和工人指针的生命周期，需要智能指针
	AFactory* aFactory = new AFactory();
	aFactory->MakeDoor()->Open();
	aFactory->MakeWorker()->Work();

	delete aFactory;
	aFactory = nullptr;
	

	system("pause");
	return 0;

}