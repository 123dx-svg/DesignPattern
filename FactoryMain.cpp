#include <iostream>

//抽象产品
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

//抽象工厂
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
//返回实际产品Human
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

// 类中有一些通用的处理逻辑，但是具体子类运行时才能确定，因此使用工厂模式可以将具体子类的创建和运行分离开来。
int main()
{

//隐藏创建细节，只暴露接口
   SpawnFactory* factory = new HumanFactory();
   factory->ExecuteAttack();
   Anim* anim = factory->CreateAnim();
   anim->Attack();
   delete anim;

   factory = new MonsterFactory();
   factory->ExecuteAttack();



    return 0;
}   