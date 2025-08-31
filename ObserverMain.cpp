#include <iostream>
#include <vector>

//��λ��Ϣ
class JobPost {
private:
std::string title;
public:

JobPost(std::string title) : title(title) {}

std::string getTitle() const {
		return title;
	}
};

//�۲��߽ӿ�
class Observer {
public:
	//֪ͨ�۲���
	virtual void OnJobPosted(JobPost* jobPost) = 0;
};
//����۲���
class JobSeeker : public Observer {
private:
	std::string name;
public:
	JobSeeker(std::string name) : name(name) {}

	void OnJobPosted(JobPost* jobPost) override {
		std::cout << name << " received a new job post: " << jobPost->getTitle() << std::endl;
	}
};

//�ɹ۲�ӿ�
class Observable {
public:
	virtual void RegisterObserver(Observer* observer) = 0;
	virtual void RemoveObserver(Observer* observer) = 0;
	virtual void NotifyObservers(JobPost* jobPost) = 0;

};
//����ɹ۲����
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

//1�Զ�
int main()
{

//�����ɹ۲����
	JobSeeker* Daniel = new JobSeeker("Daniel");
	JobSeeker* John = new JobSeeker("John");
	//��Ƹ����
	EmploymentAgency* agency = new EmploymentAgency();
	//ע��۲���
	agency->RegisterObserver(Daniel);	
	agency->RegisterObserver(John);
	//������Ƹ��Ϣ
	agency->AddJobPost(new JobPost("Software Engineer"));


	return 0;

}