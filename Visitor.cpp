#include <iostream>
#include <string>
class AnimalVisitor ;

class Animal {
public:
	virtual void accept(AnimalVisitor* visitor) = 0;
};

class Monkey;
class Lion;
class Dolphin;

class AnimalVisitor {

public:
	virtual void visitMonkey(Monkey* monkey) = 0;
	virtual void visitLion(Lion* lion) = 0;
	virtual void visitDolphin(Dolphin* dolphin) = 0;
};

class Monkey : public Animal {
public:
	void accept(AnimalVisitor* visitor) override{
		visitor->visitMonkey(this);
	}
};
class Lion : public Animal {
public:
	void accept(AnimalVisitor* visitor) override {
		visitor->visitLion(this);
	}
};
class Dolphin : public Animal {
public:
	void accept(AnimalVisitor* visitor) override {
		visitor->visitDolphin(this);
	}
};

class Speaker : public AnimalVisitor {
public:
	void visitMonkey(Monkey* monkey) override {
		std::cout << "Ooh oo aa aa!" << std::endl;
	}
	void visitLion(Lion* lion) override {
		std::cout << "Roar!" << std::endl;
	}
	void visitDolphin(Dolphin* dolphin) override {
		std::cout << "Tuut tuttu tuutt!" << std::endl;
	}
};

class Jumper : public AnimalVisitor {
public:
	void visitMonkey(Monkey* monkey) override {
		std::cout << "Jumping..." << std::endl;
	}
	void visitLion(Lion* lion) override {
		std::cout << "Grr..." << std::endl;
	}
	void visitDolphin(Dolphin* dolphin) override {
		std::cout << "Splash!" << std::endl;
	}
};

//�����ǡ��㷨�滻�����������ǡ�������չ��
//װ����ģʽ�Ǹ���������̬���ְ�� �����һ�����  ����ģʽֻ�����ұ���ʱ��ȷ��
/*UClass �� ForEachXXX �������������� UObject ��ִ�в���
TObjectIterator�������ض����͵Ķ���
Blueprint Compiler�������ڵ��������ֽ��� �� �����Ƿ�����
Serialization ϵͳ���Բ�ͬ��������ִ�в�ͬ���л��߼�
*/
int main()
{

	Animal* animals[] = { new Monkey(), new Lion(), new Dolphin() };
	Speaker* speaker = new Speaker();
	Jumper* jumper = new Jumper();
	for (int i = 0; i < 3; i++)
		animals[i]->accept(jumper);


	system("pause");
	return 0;

}