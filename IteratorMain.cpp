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
//具体迭代器
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

//具体集合
class BookShelf : public Colleciton
{
private:
	std::vector<std::string> books;

public:
	void addBook(std::string book) {
		books.push_back(book);
	}
	//创建迭代器
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



//把“遍历”这个行为从集合中分离出来，交给一个独立的“迭代器”对象来做
/*
客户端不需要知道 BookShelf 是用 vector、list 还是链表实现的。
集合的内部结构被完全封装。
遍历逻辑集中在 BookShelfIterator 中，复用性强。
支持多种遍历方式（比如反向遍历、按条件过滤等），只需新增不同的 Iterator 子类。

迭代器模式让你“如何存储”和“如何遍历”彻底解耦，客户端只需关心“有没有下一个”和“下一个是什么”，而不用管底层是数组、链表还是树。
*/
int main()
{

	BookShelf* bookshelf = new BookShelf();
	bookshelf->addBook("book1");
	bookshelf->addBook("book2");
	bookshelf->addBook("book3");

	Iterator* iterator = bookshelf->createIterator();
	//统一了接口 集合内部完全被隐藏
	while (iterator->hasNext()) {
		std::cout << iterator->next() << std::endl;
	}

	return 0;

}