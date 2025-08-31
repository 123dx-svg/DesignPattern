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

//策略是“算法替换”，访问者是“操作扩展”
//装饰器模式是给单个对象动态添加职责 这个是一组对象  访问模式只访问且编译时就确定
/*UClass 的 ForEachXXX 函数：遍历所有 UObject 并执行操作
TObjectIterator：遍历特定类型的对象
Blueprint Compiler：遍历节点树生成字节码 → 本质是访问者
Serialization 系统：对不同属性类型执行不同序列化逻辑
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