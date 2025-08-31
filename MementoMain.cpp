#include <iostream>
#include <vector>

//存储对象状态 备忘录
class Memento {
private:
	std::string state;
	public:
	Memento(std::string state) : state(state) {}
	std::string getState() { return state; }
};

//控制如何保存和恢复，保证一致性
class TextEditor {
private:
  std::string content;
public:
  void type(std::string words) {
    content += words;
  }

  std::string getContent() {
    return content;
  }

  //创建备忘录
  Memento save() {
    return Memento(content);
  }
  //恢复备忘录
  void restore(Memento memento) {
    content = memento.getState();
    }
};

//管理备忘录 Caretaker 不能读取或修改 Memento 的内容，只能“存”和“取”
//配合命令模式，可以实现撤销和恢复功能
class Caretaker {
private:
  std::vector<Memento> mementos;
public:
  void add(Memento memento) {
    mementos.push_back(memento);
  }

  Memento get(int index) {
    return mementos[index];
  }
};

//我想记住某个对象“之前的样子”，以后能把它“还原”回来，但又不能直接暴露它的私有成员。
int main()
{
    //创建备忘录，可以恢复到备忘录所记录的状态
    TextEditor* editor = new TextEditor();
    //负责保存 Memento，但不关心也不修改其内容
    Caretaker* caretaker = new Caretaker();

    editor->type("Hello, world!");
    caretaker->add(editor->save());

    editor->type("I love programming.");
    caretaker->add(editor->save());

    editor->restore(caretaker->get(0));
    std::cout <<"First========" << editor->getContent() << std::endl; 
        
    editor->restore(caretaker->get(1));
    std::cout << "Second========" << editor->getContent() << std::endl;
    // Output: Hello, world!



	return 0;

}