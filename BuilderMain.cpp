#include <iostream>
#include <string>

class Door;
//构造器放在栈上，避免构造对象时频繁的内存分配和释放，提高效率
class DoorBuilder
{
public:
	//参数默认值
	DoorBuilder():height(0),width(0),thickness(0),isWooden(false),woodType("NULL"){}

	~DoorBuilder(){std::cout<<"DoorBuilder destructor called"<< std::endl ;}

	DoorBuilder& setHeight(int height)
	{
		this->height = height;
		return *this;
	}
	DoorBuilder& setWidth(int width)
	{
		this->width = width;
		return *this;
	}
	DoorBuilder& setThickness(int thickness)
	{
		this->thickness = thickness;
		return *this;
	}
	DoorBuilder& setIsWooden(bool isWooden)
	{
		this->isWooden = isWooden;
		return *this;
	}
	DoorBuilder& setWoodType(std::string woodType)
	{
		this->woodType = woodType;
		return *this;
	}
	Door* build() const;
	

	int height;
	int width;
	int thickness;
	bool isWooden;
	std::string woodType;
};

class Door
{
public:

	Door(const DoorBuilder* builder)
	{
		height = builder->height;
		width = builder->width;
		thickness = builder->thickness;
		isWooden = builder->isWooden;
		woodType = builder->woodType;
	}
	~Door(){std::cout<<"Door destructor called"<< std::endl ;}

	void print()
	{
		std::cout << "Height: " << height << std::endl;
		std::cout << "Width: " << width << std::endl;
		std::cout << "Thickness: " << thickness << std::endl;
		
		std::cout << "isWooden:" <<  (isWooden ? "true" : "false") << std::endl;
		std::cout << "Wood Type: " << woodType << std::endl;
			
	}	

	int height;
	int width;
	int thickness;
	bool isWooden;	
	std::string woodType;

};
//这得放在最后，因为它依赖于DoorBuilder的定义
Door* DoorBuilder::build() const
{
	return new Door(this);
}


//如果对象的构造函数参数过多，则可以使用建造者模式来一步一步构造对象，使得创建对象变得更加简单、灵活。

//1、参数多（>4）且部分可选
//2、参数之间有复杂约束				在 build() 中集中验证
//3、对象构造步骤多或有顺序			分步构建，逻辑清晰
//4、需要不可变对象（immutable）	先 build 再使用
//5、构造逻辑复杂（如依赖其他服务） 将构造逻辑封装在 Builder 中
int main()
{
	
	//栈上构造对象
	Door* door1 = DoorBuilder()
		.setHeight(10)
		.setWidth(20)
		.setThickness(3)
		.setIsWooden(true)
		.setWoodType("Oak")
		.build();

	door1->print();
	delete door1;

    system("pause");
	return 0;

}