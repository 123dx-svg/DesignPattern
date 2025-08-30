#include <iostream>
#include <vector>

class File {

public:	
	void getName() {
		std::cout << "File name: " << name << std::endl;
	}
	virtual void AddFile(File* file) = 0;

	std::string name;
};

class JpgFile : public File {
public:
	JpgFile(std::string name) {
		this->name = name;
	}
	void AddFile(File* file) {
		std::cout << "Cannot add file to JpgFile" << std::endl;
	}
};

class PdfFile : public File {
public:
	PdfFile(std::string name) {
		this->name = name;
	}
	void AddFile(File* file) {
		std::cout << "Cannot add file to PdfFile" << std::endl;
	}
};

class Folder : public File {
public:
	Folder(std::string name) {
		this->name = name;
	}
	void AddFile(File* file) {
		files.push_back(file);
	}
	void printFiles() {
		for (File* file : files) {
			file->getName();
		}
	}
private:
	std::vector<File*> files;

};

//�ͻ��˿���һ�µش������������϶����������֡��ļ����͡��ļ��С���
//����ģ���ļ�ϵͳ��UI �㼶������ͼ�ȵݹ�ṹ
//�������  UI�㼶
int main()
{

	JpgFile jpg1("jpg1.jpg");
	JpgFile jpg2("jpg2.jpg");
	PdfFile pdf1("pdf1.pdf");
	PdfFile pdf2("pdf2.pdf");
	Folder folder1("folder1");
	Folder folder2("sub");
	folder1.AddFile(&folder2);
	folder1.AddFile(&jpg2);
	folder2.AddFile(&pdf1);
	folder1.AddFile(&pdf2);

	folder1.printFiles();

	return 0;

}