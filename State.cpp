#include <iostream>
#include <string>

// ǰ������
class CoffeeMachine;  // �� �ؼ��������� CoffeeMachine

// ״̬�ӿ�
class ICoffeeMachineState {
public:
	virtual void insertCoin() = 0;
	virtual void selectCoffee() = 0;
	virtual void dispenseCoffee() = 0;
	virtual ~ICoffeeMachineState() = default; // ��ϰ�ߣ�������
};

// ����״̬�ࣨ�ȶ��壩
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

// �����ٶ��� CoffeeMachine
class CoffeeMachine {
	ICoffeeMachineState* idleState;
	ICoffeeMachineState* selectingState;
	ICoffeeMachineState* dispensingState;
	ICoffeeMachineState* currentState;

public:
	CoffeeMachine();
	~CoffeeMachine(); // �ǵ��ͷ��ڴ棡

	void setState(ICoffeeMachineState* state);
	ICoffeeMachineState* getIdleState();
	ICoffeeMachineState* getSelectingState();
	ICoffeeMachineState* getDispensingState();

	void insertCoin();
	void selectCoffee();
	void dispenseCoffee();
};

// ʵ��״̬�෽��
IdleState::IdleState(CoffeeMachine* machine) : coffeeMachine(machine) {}

void IdleState::insertCoin() {
	std::cout << "Ӳ���Ѳ��룬��ѡ�񿧷ȡ�" << std::endl;
	coffeeMachine->setState(coffeeMachine->getSelectingState());
}

void IdleState::selectCoffee() {
	std::cout << "���Ȳ���Ӳ��" << std::endl;
}

void IdleState::dispenseCoffee() {
	std::cout << "���Ȳ���Ӳ�Ҳ�ѡ�񿧷�" << std::endl;
}

SelectingState::SelectingState(CoffeeMachine* machine) : coffeeMachine(machine) {}

void SelectingState::insertCoin() {
	std::cout << "Ӳ���Ѳ��룬�벻Ҫ�ظ�Ͷ�ң���" << std::endl;
}

void SelectingState::selectCoffee() {
	std::cout << "����������" << std::endl;
	coffeeMachine->setState(coffeeMachine->getDispensingState());
}

void SelectingState::dispenseCoffee() {
	std::cout << "����ѡ�񿧷�" << std::endl;
}

DispensingState::DispensingState(CoffeeMachine* machine) : coffeeMachine(machine) {}

void DispensingState::insertCoin() {
	std::cout << "Ӳ���Ѳ��룬�벻Ҫ�ظ�Ͷ�ң���" << std::endl;
}

void DispensingState::selectCoffee() {
	std::cout << "�����������ȣ���ȴ�..." << std::endl;
}

void DispensingState::dispenseCoffee() {
	std::cout << "�����ѳ�" << std::endl;
	coffeeMachine->setState(coffeeMachine->getIdleState());
}

// ʵ�� CoffeeMachine ����
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

// ������
int main() {
	CoffeeMachine* coffeeMachine = new CoffeeMachine();

	// ��ȷ��ʹ�÷�ʽ��ͨ�� CoffeeMachine ����
	coffeeMachine->insertCoin();        // �� SelectingState
	coffeeMachine->selectCoffee();      // �� DispensingState
	coffeeMachine->dispenseCoffee();    // �� IdleState

	delete coffeeMachine;
	return 0;
}