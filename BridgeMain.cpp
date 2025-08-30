#include <iostream>

class Color {
	public:
	virtual void setColor() = 0;
};

class Red : public Color {
	public:
		virtual void  setColor() override
		{
			std::cout << "Red color" << std::endl;
		}
};

class Green : public Color {
	public:
		virtual void  setColor() override
		{
			std::cout << "Green color" << std::endl;
		}
};

class Shape {
public:
	Shape(Color* color) {
		this->color = color;
	}

	virtual void draw() = 0;

	// 桥接点：持有实现类的指针
	Color* color;
};

class Circle : public Shape {
public:
	Circle(Color* color) : Shape(color) {}

	void draw() override
	{
		color->setColor();
		std::cout << "Drawing Circle" << std::endl;
	}
};

class Rectangle : public Shape {
public:
	Rectangle(Color* color) : Shape(color) {}

	void draw() override
	{
		color->setColor();
		std::cout << "Drawing Rectangle" << std::endl;
	}
};

/// <summary>
///非必须类，用于测试
/// </summary>
class BridgePattern {
public:
	BridgePattern() {}

	Color* redColor = new Red();
	Color* greenColor = new Green();
	Shape* circle = new Circle(redColor);
	Shape* rectangle = new Rectangle(greenColor);

	void drawCircle()
	{
		circle->draw();
	}

	void drawRectangle()
	{
		rectangle->draw();
	}

};


//Shape 和 Color 完全分离，可以独立修改
//加新颜色（如 Blue）只需继承 Color。加新形状（如 Triangle）只需继承 Shape。无需修改现有代码
int main()
{
	BridgePattern bridgePattern;

	bridgePattern.drawCircle();
	bridgePattern.drawRectangle();

	


	return 0;

}