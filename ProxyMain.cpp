#include <iostream>

class Door {

public:
	virtual void open(std::string const& password) = 0;
	virtual void close() = 0;

};

class RealDoor : public Door {

public:
	void open(std::string const& password) override {
		std::cout << "Real door will open " << std::endl;
	}

	void close() override {
		std::cout << "Real door will close " << std::endl;
	}

};

class SecureDoor : public Door {
private:
	Door* door;
	
public:
	SecureDoor(Door* door) : door(door) {}

	//有条件的调用原对象
	void open(std::string const& password) override {
		if (ComparePassword(password)) {
			door->open(password);
		}
		else {
			std::cout << "Wrong password " << std::endl;
		}
	}

	void close() override {
		door->close();
	}

	bool ComparePassword(std::string const& password) {
		return password=="1234";
	}
};

int main()
{

	Door* door = new SecureDoor(new RealDoor());
	door->open("1234");
	door->close();


	return 0;

}