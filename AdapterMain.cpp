#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

//Ŀ��ӿ�
class MediaPlayer {
public:
	virtual void Play(std::string videoType,std::string fileName) = 0;

};

//���нӿ�
class AdvancedMediaPlayer {
public:
	virtual	void PlayVlc(std::string fileName) = 0;
	virtual void PlayAvi(std::string fileName) = 0;
};

class VlcPlayer : public AdvancedMediaPlayer {
public:
	void PlayVlc(std::string fileName) override{
		std::cout << "Playing VLC file: " << fileName << std::endl;
	}
	void PlayAvi(std::string fileName) override {}
};
class AviPlayer : public AdvancedMediaPlayer {
public:
	void PlayVlc(std::string fileName) override {}
	void PlayAvi(std::string fileName) override {
		std::cout << "Playing Avi file: " << fileName << std::endl;
	}
};

//������
class MediaAdapter : public MediaPlayer {

public:

	MediaAdapter():vlcPlayer(new VlcPlayer()), aviPlayer(new AviPlayer()) {
		PlayerMap["vlc"] = [p = std::move(vlcPlayer)](const std::string& fileName) {p->PlayVlc(fileName);};
		PlayerMap["avi"] = [p = std::move(aviPlayer)](const std::string& fileName) {p->PlayAvi(fileName);};
	
	}

	virtual void Play(std::string videoType, std::string fileName) override {
		
		if (PlayerMap.count(videoType)){
			PlayerMap[videoType](fileName);
		}
	}

	AdvancedMediaPlayer* vlcPlayer;
	AdvancedMediaPlayer* aviPlayer;

private:
//ӳ���
	std::unordered_map<std::string, std::function<void(const std::string&)>> PlayerMap;

};

class VedioPlayer : public MediaPlayer {
public:
	VedioPlayer():mediaAdapter(new MediaAdapter()) {}

	void Play(std::string videoType, std::string fileName) override {
		if (videoType == "vlc" || videoType == "avi")
		{
			mediaAdapter->Play(videoType, fileName);
		}
		else if (videoType == "mp4")
		{
			std::cout << "Playing mp4 file: " << fileName << std::endl;
		}
		else
		{
			std::cout << "Unsupported video type: " << videoType << std::endl;
		}
	}

	MediaAdapter* mediaAdapter;
};	

//��һ�ֽӿ�ת������һ�ֽӿ�
int main()
{
	VedioPlayer* vedioPlayer = new VedioPlayer();
	//��һ�ֽӿ�ת������һ�ֽӿ�
	vedioPlayer->Play("vlc", "vlc.mp4");
	vedioPlayer->Play("avi", "avi.mp4");
	vedioPlayer->Play("mp4", "mp4.mp4");

	system("pause");
	return 0;

}