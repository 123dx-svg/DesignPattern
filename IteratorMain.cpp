#include <iostream>
#include <vector>

class Iterator
{
public:
	virtual bool hasNext() = 0;
	virtual std::string next() = 0;

	virtual ~Iterator() {}
};

class Colleciton {
public:
	virtual Iterator* createIterator() = 0;

	virtual ~Colleciton() {}
};

class BookShelf;
//���������
class BookShelfIterator : public Iterator {
private:
	BookShelf* bookshelf;
	int index = 0;
public:
	BookShelfIterator(BookShelf* bookshelf) :bookshelf(bookshelf), index(0) {
	};

	bool hasNext() override;

	std::string next() override ;

};

//���弯��
class BookShelf : public Colleciton
{
private:
	std::vector<std::string> books;

public:
	void addBook(std::string book) {
		books.push_back(book);
	}
	//����������
	Iterator* createIterator() override
	{
		return new BookShelfIterator(this);
	};

	const std::vector<std::string>& getBooks() {
		return books;
	}
};

bool BookShelfIterator::hasNext() {
	return index < bookshelf->getBooks().size();
}
std::string BookShelfIterator::next() {
	if (hasNext()) {
		return bookshelf->getBooks()[index++];
	}
	return "";
}



//�ѡ������������Ϊ�Ӽ����з������������һ�������ġ�����������������
/*
�ͻ��˲���Ҫ֪�� BookShelf ���� vector��list ��������ʵ�ֵġ�
���ϵ��ڲ��ṹ����ȫ��װ��
�����߼������� BookShelfIterator �У�������ǿ��
֧�ֶ��ֱ�����ʽ�����練����������������˵ȣ���ֻ��������ͬ�� Iterator ���ࡣ

������ģʽ���㡰��δ洢���͡���α��������׽���ͻ���ֻ����ġ���û����һ�����͡���һ����ʲô���������ùܵײ������顢����������
*/
int main()
{

	BookShelf* bookshelf = new BookShelf();
	bookshelf->addBook("book1");
	bookshelf->addBook("book2");
	bookshelf->addBook("book3");

	Iterator* iterator = bookshelf->createIterator();
	//ͳһ�˽ӿ� �����ڲ���ȫ������
	while (iterator->hasNext()) {
		std::cout << iterator->next() << std::endl;
	}

	return 0;

}