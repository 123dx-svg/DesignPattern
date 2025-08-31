#include <iostream>
#include <vector>
class User;

class ChatMediator {
public:
   virtual void sendMessage(const std::string& message, User* User) = 0;
   virtual void addUser(User* user) = 0;
};

//具体中介者：聊天室
class ChatMediatorImpl : public ChatMediator {
private:
//所有用户
   std::vector<User*> users;

public:
	ChatMediatorImpl(){}

	//广播消息
	void sendMessage(const std::string& message, User* user) override;
	//新增用户
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

//具体用户
class UserImpl : public User {
public:
	UserImpl(ChatMediator* med, const std::string& inName) : User(med, inName) {}

	//委托中介者发送消息
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
			//不发给自己
			if (u != user) {
				u->receiveMessage("From" + user->name + ": " + message);
			}
		}
	}
}

int main()
{

	ChatMediator* mediator = new ChatMediatorImpl();
	//通过中介者
	User* user1 = new UserImpl(mediator, "Alice");
	User* user2 = new UserImpl(mediator, "Bob");
	User* user3 = new UserImpl(mediator, "Charlie");

	//加入聊天室
	mediator->addUser(user1);
	mediator->addUser(user2);
	mediator->addUser(user3);

	//发送消息
	user1->send("Hello, everyone!");
	
	

	return 0;

}