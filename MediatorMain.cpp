#include <iostream>
#include <vector>
class User;

class ChatMediator {
public:
   virtual void sendMessage(const std::string& message, User* User) = 0;
   virtual void addUser(User* user) = 0;
};

//�����н��ߣ�������
class ChatMediatorImpl : public ChatMediator {
private:
//�����û�
   std::vector<User*> users;

public:
	ChatMediatorImpl(){}

	//�㲥��Ϣ
	void sendMessage(const std::string& message, User* user) override;
	//�����û�
	void addUser(User* user) override {
		users.push_back(user);
	}

 };

class User {

public:
	ChatMediator* mediator;
	std::string name;

public:
	User(ChatMediator* med, const std::string& inName) : mediator(med), name(inName) {}

	virtual ~User() {}

	virtual void send(std::string message) = 0;
	virtual void receiveMessage(const std::string& message) = 0;

};

//�����û�
class UserImpl : public User {
public:
	UserImpl(ChatMediator* med, const std::string& inName) : User(med, inName) {}

	//ί���н��߷�����Ϣ
	void send(std::string message) override {
		std::cout << this->name<<" sent message: "<<message<<std::endl;
		mediator->sendMessage(message, this);
	}
	void receiveMessage(const std::string& message) override {
		std::cout << this->name << "received message: " << message << std::endl;
	}
};


void ChatMediatorImpl::sendMessage(const std::string& message, User* user) {
	{
		for (User* u : users) {
			//�������Լ�
			if (u != user) {
				u->receiveMessage("From" + user->name + ": " + message);
			}
		}
	}
}

int main()
{

	ChatMediator* mediator = new ChatMediatorImpl();
	//ͨ���н���
	User* user1 = new UserImpl(mediator, "Alice");
	User* user2 = new UserImpl(mediator, "Bob");
	User* user3 = new UserImpl(mediator, "Charlie");

	//����������
	mediator->addUser(user1);
	mediator->addUser(user2);
	mediator->addUser(user3);

	//������Ϣ
	user1->send("Hello, everyone!");
	
	

	return 0;

}