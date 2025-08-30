#include <iostream>
#include <string>

class Door;
//����������ջ�ϣ����⹹�����ʱƵ�����ڴ������ͷţ����Ч��
class DoorBuilder
{
public:
	//����Ĭ��ֵ
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
//��÷��������Ϊ��������DoorBuilder�Ķ���
Door* DoorBuilder::build() const
{
	return new Door(this);
}


//�������Ĺ��캯���������࣬�����ʹ�ý�����ģʽ��һ��һ���������ʹ�ô��������ø��Ӽ򵥡���

//1�������ࣨ>4���Ҳ��ֿ�ѡ
//2������֮���и���Լ��				�� build() �м�����֤
//3�������첽������˳��			�ֲ��������߼�����
//4����Ҫ���ɱ����immutable��	�� build ��ʹ��
//5�������߼����ӣ��������������� �������߼���װ�� Builder ��
int main()
{
	
	//ջ�Ϲ������
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