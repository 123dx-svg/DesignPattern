#include <iostream>
#include <vector>

//岗位信息
class JobPost {
private:
std::string title;
public:

JobPost(std::string title) : title(title) {}

std::string getTitle() const {
		return title;
	}
};

//观察者接口
class Observer {
public:
	//通知观察者
	virtual void OnJobPosted(JobPost* jobPost) = 0;
};
//具体观察者
class JobSeeker : public Observer {
private:
	std::string name;
public:
	JobSeeker(std::string name) : name(name) {}

	void OnJobPosted(JobPost* jobPost) override {
		std::cout << name << " received a new job post: " << jobPost->getTitle() << std::endl;
	}
};

//可观察接口
class Observable {
public:
	virtual void RegisterObserver(Observer* observer) = 0;
	virtual void RemoveObserver(Observer* observer) = 0;
	virtual void NotifyObservers(JobPost* jobPost) = 0;

};
//具体可观察对象
class EmploymentAgency : public Observable {
 private:
	std::vector<Observer*> observers;
 public:
	void RegisterObserver(Observer* observer) override {
		observers.push_back(observer);
	}

	void RemoveObserver(Observer* observer) override {
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}

	void NotifyObservers(JobPost* jobPost) override {
		for (Observer* observer : observers) {
			observer->OnJobPosted(jobPost);
		}
	}

	void AddJobPost(JobPost* jobPost) {
		NotifyObservers(jobPost);
	}
};

//1对多
int main()
{

//创建可观察对象
	JobSeeker* Daniel = new JobSeeker("Daniel");
	JobSeeker* John = new JobSeeker("John");
	//招聘机构
	EmploymentAgency* agency = new EmploymentAgency();
	//注册观察者
	agency->RegisterObserver(Daniel);	
	agency->RegisterObserver(John);
	//发布招聘信息
	agency->AddJobPost(new JobPost("Software Engineer"));


	return 0;

}