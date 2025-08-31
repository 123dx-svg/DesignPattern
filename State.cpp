#include <iostream>
#include <string>

// 前向声明
class CoffeeMachine;  // ← 关键：先声明 CoffeeMachine

// 状态接口
class ICoffeeMachineState {
public:
	virtual void insertCoin() = 0;
	virtual void selectCoffee() = 0;
	virtual void dispenseCoffee() = 0;
	virtual ~ICoffeeMachineState() = default; // 好习惯：虚析构
};

// 具体状态类（先定义）
class IdleState : public ICoffeeMachineState {
private:
	CoffeeMachine* coffeeMachine;
public:
	IdleState(CoffeeMachine* coffeeMachine);
	void insertCoin() override;
	void selectCoffee() override;
	void dispenseCoffee() override;
};

class SelectingState : public ICoffeeMachineState {
private:
	CoffeeMachine* coffeeMachine;
public:
	SelectingState(CoffeeMachine* coffeeMachine);
	void insertCoin() override;
	void selectCoffee() override;
	void dispenseCoffee() override;
};

class DispensingState : public ICoffeeMachineState {
private:
	CoffeeMachine* coffeeMachine;
public:
	DispensingState(CoffeeMachine* coffeeMachine);
	void insertCoin() override;
	void selectCoffee() override;
	void dispenseCoffee() override;
};

// 现在再定义 CoffeeMachine
class CoffeeMachine {
	ICoffeeMachineState* idleState;
	ICoffeeMachineState* selectingState;
	ICoffeeMachineState* dispensingState;
	ICoffeeMachineState* currentState;

public:
	CoffeeMachine();
	~CoffeeMachine(); // 记得释放内存！

	void setState(ICoffeeMachineState* state);
	ICoffeeMachineState* getIdleState();
	ICoffeeMachineState* getSelectingState();
	ICoffeeMachineState* getDispensingState();

	void insertCoin();
	void selectCoffee();
	void dispenseCoffee();
};

// 实现状态类方法
IdleState::IdleState(CoffeeMachine* machine) : coffeeMachine(machine) {}

void IdleState::insertCoin() {
	std::cout << "硬币已插入，请选择咖啡。" << std::endl;
	coffeeMachine->setState(coffeeMachine->getSelectingState());
}

void IdleState::selectCoffee() {
	std::cout << "请先插入硬币" << std::endl;
}

void IdleState::dispenseCoffee() {
	std::cout << "请先插入硬币并选择咖啡" << std::endl;
}

SelectingState::SelectingState(CoffeeMachine* machine) : coffeeMachine(machine) {}

void SelectingState::insertCoin() {
	std::cout << "硬币已插入，请不要重复投币！！" << std::endl;
}

void SelectingState::selectCoffee() {
	std::cout << "咖啡制作中" << std::endl;
	coffeeMachine->setState(coffeeMachine->getDispensingState());
}

void SelectingState::dispenseCoffee() {
	std::cout << "请先选择咖啡" << std::endl;
}

DispensingState::DispensingState(CoffeeMachine* machine) : coffeeMachine(machine) {}

void DispensingState::insertCoin() {
	std::cout << "硬币已插入，请不要重复投币！！" << std::endl;
}

void DispensingState::selectCoffee() {
	std::cout << "正在制作咖啡，请等待..." << std::endl;
}

void DispensingState::dispenseCoffee() {
	std::cout << "咖啡已出" << std::endl;
	coffeeMachine->setState(coffeeMachine->getIdleState());
}

// 实现 CoffeeMachine 方法
CoffeeMachine::CoffeeMachine() {
	idleState = new IdleState(this);
	selectingState = new SelectingState(this);
	dispensingState = new DispensingState(this);
	currentState = idleState;
}

CoffeeMachine::~CoffeeMachine() {
	delete idleState;
	delete selectingState;
	delete dispensingState;
}

void CoffeeMachine::setState(ICoffeeMachineState* state) {
	currentState = state;
}

ICoffeeMachineState* CoffeeMachine::getIdleState() {
	return idleState;
}

ICoffeeMachineState* CoffeeMachine::getSelectingState() {
	return selectingState;
}

ICoffeeMachineState* CoffeeMachine::getDispensingState() {
	return dispensingState;
}

void CoffeeMachine::insertCoin() {
	currentState->insertCoin();
}

void CoffeeMachine::selectCoffee() {
	currentState->selectCoffee();
}

void CoffeeMachine::dispenseCoffee() {
	currentState->dispenseCoffee();
}

// 主函数
int main() {
	CoffeeMachine* coffeeMachine = new CoffeeMachine();

	// 正确的使用方式：通过 CoffeeMachine 调用
	coffeeMachine->insertCoin();        // → SelectingState
	coffeeMachine->selectCoffee();      // → DispensingState
	coffeeMachine->dispenseCoffee();    // → IdleState

	delete coffeeMachine;
	return 0;
}