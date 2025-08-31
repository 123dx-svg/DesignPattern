#include <iostream>
#include <vector>

//�洢����״̬ ����¼
class Memento {
private:
	std::string state;
	public:
	Memento(std::string state) : state(state) {}
	std::string getState() { return state; }
};

//������α���ͻָ�����֤һ����
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

  //��������¼
  Memento save() {
    return Memento(content);
  }
  //�ָ�����¼
  void restore(Memento memento) {
    content = memento.getState();
    }
};

//������¼ Caretaker ���ܶ�ȡ���޸� Memento �����ݣ�ֻ�ܡ��桱�͡�ȡ��
//�������ģʽ������ʵ�ֳ����ͻָ�����
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

//�����סĳ������֮ǰ�����ӡ����Ժ��ܰ�������ԭ�����������ֲ���ֱ�ӱ�¶����˽�г�Ա��
int main()
{
    //��������¼�����Իָ�������¼����¼��״̬
    TextEditor* editor = new TextEditor();
    //���𱣴� Memento����������Ҳ���޸�������
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