
#include <iostream>
class Door {
public:

public:
    virtual float GetWidth() = 0;
    virtual float GetHeight() = 0;
};

class WoodenDoor : public Door {

public:
    WoodenDoor(float width, float height) : m_width(width), m_height(height) {}

    virtual float GetWidth() {
        return m_width;
    }

    virtual float GetHeight() {
        return m_height;
    }
private:
    float m_width;
    float m_height;

};
class GlassDoor : public Door {

public:
    GlassDoor(float width, float height) : m_width(width), m_height(height) {}

	virtual float GetWidth() {
		return m_width;
	}

	virtual float GetHeight() {
		return m_height;
	}
private:
	float m_width;
	float m_height;

};

//如果创建非常复杂建议使用简单工厂模式    但是随着要创建的对象数量的增加，简单工厂模式会变得越来越复杂，不利于维护和扩展
class DoorFactory {
public:
    static Door* CreateDoor(float width, float height, std::string type = "wooden") {
        if (type == "wooden") {
            return new WoodenDoor(width, height);
        }
        else if (type == "glass") {
            return new GlassDoor(width, height);
        }
        return nullptr;
    }
             
};


int main()
{
    

    Door* door2 = DoorFactory::CreateDoor(15, 25, "glass");
    std::cout << "Width: " << door2->GetWidth() << std::endl;
    std::cout << "Height: " << door2->GetHeight() << std::endl;


    delete door2;


    return 0;

}