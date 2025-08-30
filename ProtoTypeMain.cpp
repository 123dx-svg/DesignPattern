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
	//�������캯��
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
	//���ÿ�������  ��ʱ��ֱ�ӷ���Shape* ����Ҳ�Ͳ�����Ҫcast�� ���ǻ��ƻ�Cloneable�ӿ�
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
		//���ÿ�������
		return new Cube(*this);
	}


};

//ԭ�͹�����
class ShapePrototypeManager
{
public:
	static void initPrototype() {
	//��ֹ�ظ���ʼ��
		if (!m_shapeMap.empty())
			return;
		//��ʼ��ԭ�͹����� ���ԭ�Ͷ���
		m_shapeMap["Circle"] = new Circle();
		m_shapeMap["Cube"] = new Cube();

    }

	static Shape* create(const std::string& name) {
		//��ԭ�͹������л�ȡԭ�Ͷ��� ��ȷ����ʼ��
		initPrototype();
		auto it = m_shapeMap.find(name);
		if (it != m_shapeMap.end()) {
			std::cout << "Shape  founded !" << std::endl;
			//���ؿ�¡���� static_cast���ܸ���
			return static_cast<Shape*>(it->second->clone());
		}
	
		return nullptr;
	
	}

private:
   static std::unordered_map<std::string, Shape*> m_shapeMap;

};

std::unordered_map<std::string, Shape*> ShapePrototypeManager::m_shapeMap;


/*
	m_shapeMap["Cube"] ��ԭ�ͣ�prototype�� ���� ֻ��һ������פ�ڴ档
	shape1 �� shape2 �ǿ�¡�壨clones�� ���� ÿ�� create() ��������һ���µĿ�¡��


	�������캯���ڸ�����Ĺ���ʱԶ�ȹ��캯�����ܸ�
*/
int main()
{

//����һ������
	auto shape1 = ShapePrototypeManager::create("Cube");
	auto shape2 = ShapePrototypeManager::create("Cube");
	shape2->draw();
	return 0;

}