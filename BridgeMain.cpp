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

	// �Žӵ㣺����ʵ�����ָ��
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
///�Ǳ����࣬���ڲ���
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


//Shape �� Color ��ȫ���룬���Զ����޸�
//������ɫ���� Blue��ֻ��̳� Color��������״���� Triangle��ֻ��̳� Shape�������޸����д���
int main()
{
	BridgePattern bridgePattern;

	bridgePattern.drawCircle();
	bridgePattern.drawRectangle();

	


	return 0;

}