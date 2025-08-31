#include <iostream>

//�����Ʒ
class Anim
{
public:
    virtual void Attack() = 0;
    virtual ~Anim() {}
};

class Human : public Anim
{
public:
    void Attack()
    {
        std::cout << "Human Attack" << std::endl;
    }
};
class Monster : public Anim
{
public:
    void Attack()
    {
        std::cout << "Monster Attack" << std::endl;
    }
};

//���󹤳�
class SpawnFactory
{
public:
    virtual Anim* CreateAnim() = 0;

    void ExecuteAttack()
    {
        Anim* anim = CreateAnim();
        anim->Attack();
        delete anim;    
        anim  = nullptr;
    }
};

class HumanFactory : public SpawnFactory
{
public:
//����ʵ�ʲ�ƷHuman
    Anim* CreateAnim()
    {
        return new Human();
    }
};

class MonsterFactory : public SpawnFactory
{
public:
    Anim* CreateAnim()
    {
        return new Monster();
    }
};

// ������һЩͨ�õĴ����߼������Ǿ�����������ʱ����ȷ�������ʹ�ù���ģʽ���Խ���������Ĵ��������з��뿪����
int main()
{

//���ش���ϸ�ڣ�ֻ��¶�ӿ�
   SpawnFactory* factory = new HumanFactory();
   factory->ExecuteAttack();
   Anim* anim = factory->CreateAnim();
   anim->Attack();
   delete anim;

   factory = new MonsterFactory();
   factory->ExecuteAttack();



    return 0;
}   