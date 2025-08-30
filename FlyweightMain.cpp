#include <iostream>
#include <unordered_map>
#include <random>

//����Ļ�ϻ��ƴ�С��ɫλ�ò�ͬ��Բ
class Circle {
public:
  virtual void draw() = 0;
  virtual void SetPosition(int x, int y) = 0;
};

class ConcreateCircle : public Circle {
public:
	ConcreateCircle(std::string color)
	{
		this->color = color;
	}

	void draw() override {
		std::cout << "Drawing a " << color << " circle at (" << x << ", " << y << ")" << std::endl;
	}

	void SetPosition(int x, int y) override {
		this->x = x;
		this->y = y;
	}


private:
  int x, y;
  std::string color;

};

class CircleFactory {

public:

//û�оʹ���
	static Circle* GetCircle(std::string color) {
	    Circle* circle = circleMap[color];
	    if (circle == nullptr) {
			circle = new ConcreateCircle(color);
			circleMap[color] = circle;
			std::cout << "Creating a new " << color << " circle" << std::endl;

		}
	    return circle;
	}




private:
	static std::unordered_map<std::string, Circle*> circleMap;

};

std::unordered_map<std::string, Circle*> CircleFactory::circleMap;


// �򵥵����������
int randInt(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

//��Ԫģʽͨ���漰������صĸ��ͨ�������������������Ĵ����͹���ԭ��ģʽ���������ڶ�������Ŀ�¡������������ʵ����
//����Ԫ���������Դ������������
//��ԭ�͹���ɱ����Ϸʵ�壨��ҡ����ˣ�
int main()
{
	std::string colors[] = {"red", "green", "blue","black" ,"white"};
	//ֻ�ᴴ��5����ɫ��Բ
	for (int i = 0; i < 20; i++)
	{
		Circle* circle = CircleFactory::GetCircle(colors[randInt(0, 4)]);
		circle->SetPosition(randInt(0, 100), randInt(0, 100));
		circle->draw();
	}


	// ��Ԫģʽ - ����ͬһ������
	Circle* red1 = CircleFactory::GetCircle("red");
	Circle* red2 = CircleFactory::GetCircle("red");
	// red1 �� red2 ָ��ͬһ������
	// �ڴ���ֻ��һ����ɫԲ
	return 0;

}