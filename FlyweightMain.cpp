#include <iostream>
#include <unordered_map>
#include <random>

//在屏幕上绘制大小颜色位置不同的圆
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

//没有就创建
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


// 简单的随机数函数
int randInt(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

//享元模式通常涉及到对象池的概念，通过工厂方法来管理对象的创建和共享；原型模式则是依赖于对象自身的克隆能力来创建新实例。
//用享元管理不变的资源（纹理、声音）
//用原型管理可变的游戏实体（玩家、敌人）
int main()
{
	std::string colors[] = {"red", "green", "blue","black" ,"white"};
	//只会创建5个颜色的圆
	for (int i = 0; i < 20; i++)
	{
		Circle* circle = CircleFactory::GetCircle(colors[randInt(0, 4)]);
		circle->SetPosition(randInt(0, 100), randInt(0, 100));
		circle->draw();
	}


	// 享元模式 - 共享同一个对象
	Circle* red1 = CircleFactory::GetCircle("red");
	Circle* red2 = CircleFactory::GetCircle("red");
	// red1 和 red2 指向同一个对象！
	// 内存中只有一个红色圆
	return 0;

}