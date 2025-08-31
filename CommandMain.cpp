#include <iostream>

class Bulb {
public:
	void turnOn() {
		std::cout << "Bulb turned on" << std::endl;
	}

	void turnOff() {
		std::cout << "Bulb turned off" << std::endl;
	}
};
class Command {
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual void redo() = 0;

	virtual ~Command() {}
};

class TurnOnCommand : public Command {
private:
	Bulb* bulb;
public:
	TurnOnCommand(Bulb* bulb) {
		this->bulb = bulb;
	}

	void execute() {
		bulb->turnOn();
	}
	void undo() {
		bulb->turnOff();
	}
	void redo() {
		execute();
	}
};
class TurnOffCommand : public Command {
private:
	Bulb* bulb;
public:
	TurnOffCommand(Bulb* bulb) {
		this->bulb = bulb;
	}

	void execute() {
		bulb->turnOff();
	}
	void undo() {
		bulb->turnOn();
	}
	void redo() {
		execute();
	}
};

class RemoteControl {
public:
	void submit(Command* command) {
		command->execute();		
	}
};

//撤销/重做系统（如策略游戏、编辑器）
//调用者和命令对象分离，使得调用者不必知道命令的具体实现，只需知道命令的接口。
int main()
{
	Bulb* bulb = new Bulb();

	Command* turnOn = new TurnOnCommand(bulb);
	Command* turnOff = new TurnOffCommand(bulb);

	RemoteControl remote;
	remote.submit(turnOn);
	remote.submit(turnOff);

	return 0;

}