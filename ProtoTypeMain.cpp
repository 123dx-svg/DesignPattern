#include <iostream>
#include <unordered_map>

class Cloneable {
public:
	virtual const Cloneable* clone() = 0;
	virtual ~Cloneable()=default;

};


class Shape:public Cloneable 
{
	
public:

	Shape(int id):id(id){}
	//拷贝构造函数
	Shape(const Shape& other):id(other.id),name(other.name){}

	virtual void draw() = 0;

	int getId() const
	{
		return id;
	}
	std::string getName() const
	{
		return name;
	}

	virtual Cloneable* clone() override = 0;
	

protected:
	std::string name;
	int id;
};

class Circle:public Shape
{
public:
	Circle():Shape(1)
	{
		name = "Circle";
	}

	void draw() override
	{
		std::cout<<"My Shape Is:"<<name<<"ID="<<id<<std::endl;
	}

	Cloneable* clone() override
	{
	//调用拷贝构造  有时候直接返回Shape* 后续也就不再需要cast了 但是会破坏Cloneable接口
		return new Circle(*this);
	}

};

class Cube :public Shape
{
public:
	Cube():Shape(2)
	{
		name = "Cube";
	}

	void draw() override
	{
		std::cout << "My Shape Is:" << name << ";  ID=" << id << std::endl;
	}

	Cloneable* clone() override
	{
		//调用拷贝构造
		return new Cube(*this);
	}


};

//原型管理器
class ShapePrototypeManager
{
public:
	static void initPrototype() {
	//防止重复初始化
		if (!m_shapeMap.empty())
			return;
		//初始化原型管理器 添加原型对象
		m_shapeMap["Circle"] = new Circle();
		m_shapeMap["Cube"] = new Cube();

    }

	static Shape* create(const std::string& name) {
		//从原型管理器中获取原型对象 先确保初始化
		initPrototype();
		auto it = m_shapeMap.find(name);
		if (it != m_shapeMap.end()) {
			std::cout << "Shape  founded !" << std::endl;
			//返回克隆对象 static_cast性能更高
			return static_cast<Shape*>(it->second->clone());
		}
	
		return nullptr;
	
	}

private:
   static std::unordered_map<std::string, Shape*> m_shapeMap;

};

std::unordered_map<std::string, Shape*> ShapePrototypeManager::m_shapeMap;


/*
	m_shapeMap["Cube"] 是原型（prototype） —— 只有一个，常驻内存。
	shape1 和 shape2 是克隆体（clones） —— 每次 create() 都会生成一个新的克隆。


	拷贝构造函数在复杂类的构建时远比构造函数性能高
*/
int main()
{

//不是一个对象
	auto shape1 = ShapePrototypeManager::create("Cube");
	auto shape2 = ShapePrototypeManager::create("Cube");
	shape2->draw();
	return 0;

}