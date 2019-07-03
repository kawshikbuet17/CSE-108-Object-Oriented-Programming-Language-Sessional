#include<iostream>
#include<cstring>
using namespace std;

class Unit
{
protected:
    int range;
    int health;
    int damage;
    int position;
    int cost=1600;
    //int step_size;
    int return_coin;
    char name[20];
    char shoot_type[20];
    char movement[20];
    int round=1;
public:
    virtual void setHealth(int x){health = x;}
    virtual void roundType(int p){}
    virtual void cost_update(int p){}
    int getRound(){return round;}

    int getRange(){return range;}
    int getHealth(){return health;}
    int getDamage(){return damage;}
    int getCost(){return cost;}
    //int getStepsize(){return step_size;}
    int getPosition(){return position;}
    char* getName(){return name;}
    char* getShoottype(){return shoot_type;}
    char* getMovement(){return movement;}
};

class bowman:public Unit
{
public:
    bowman(int k)
    {
        range=110;
        health=60;
        damage=10;
        position=0;
        cost=100;
        //step_size=0;
        return_coin=40;
        strcpy(name,"Bowman");
        strcpy(shoot_type,"Basic Arrow");
        strcpy(movement,"Stationary");
    }

    void roundType(int k)
    {
        health-=40;
    }
};

class advanced_bowman:public Unit
{
public:
    advanced_bowman(int k)
    {
        range=130;
        health=85;
        damage=15;
        position=0;
        cost=200;
        //step_size=0;
        return_coin=60;
        strcpy(name,"Advanced Bowman");
        strcpy(shoot_type,"Canon");
        strcpy(movement,"Stationary");
    }


    void roundType(int k)
    {
        health-=40;
    }
};

class archer:public Unit
{
public:
    archer(int k)
    {
        range=50;
        health=100;
        damage=25;
        position = 25;
        cost=150;
        //step_size=25;
        return_coin=0;
        strcpy(name,"Archer");
        strcpy(shoot_type,"Advanced Arrow");
        strcpy(movement,"Running");
    }

    void roundType(int k)
    {
        health-=40;
        position+=25;
    }
};

class advanced_archer:public Unit
{
public:
    advanced_archer(int k)
    {
        range=50;
        health=120;
        damage=50;
        position = 30;
        cost=600;
        //step_size=30;
        return_coin=0;
        strcpy(name,"Advanced Archer");
        strcpy(shoot_type,"Improved Arrow");
        strcpy(movement,"Riding horse");
    }

    void roundType(int k)
    {
        health-=40;
        position+=30;
    }
};
class enemy_tower:public Unit
{
public:
    enemy_tower(int k)
    {
        range=200;
        health=300;
        damage=40;
        cost=1600;
        position = 100;
        return_coin=0;
        strcpy(shoot_type,"Fire Arrow");
        strcpy(movement,"Stationary");
        strcpy(name, "Enemy Tower");
    }
    //void set_health(int n){health = n;}
    void cost_update(int k)
       {
          if(k==1) cost-=150;
          else if(k==2) cost-=600;
          else if(k==3)
          {
              cost-=60;
              cout<<"Bowman gave 40 coins while dying."<<endl;
          }
          else
          {
              cost-=140;
              cout<<"Advanced Bowman gave 60 coins while dying."<<endl;
          }
       }

    void roundType(int k)
       {
           if(k==1)
                health-=25;
           else if(k==2)
                health-=50;

           else if(k==3)
                health-=10;
           else
                health-=15;
       }
};




int main()
{
    int mask=1;
    Unit *w;
    Unit *e;
    e=new enemy_tower(0);
    int choice,i;

    i=e->getRound();

    while(1)
    {
        cout<<"Coin remaining "<<e->getCost()<<endl;
        cout<<"Choose your option:"<<endl;
        cout<<"1. Archer (Cost 150)"<<endl;
        cout<<"2. Advanced Archer (Cost 600)"<<endl;
        cout<<"3. Bowman (Cost 100)"<<endl;
        cout<<"4. Advanced Bowman (Cost 200)"<<endl;

        cin>>choice;

        switch(choice)
        {
            case 1: w =  new archer(0);
                    break;
            case 2: w = new advanced_archer(0);
                    break;
            case 3: w =  new bowman(0);
                    break;
            default : w = new advanced_bowman(0);
                    break;
        }

       if(w->getCost()>e->getCost())
       {
           cout<<"Game Over !!Wrong Choice !!"<<endl;
           return 0;
       }



       int j;
       //i=e->getRound();

       cout<<"Round : "<<i++<<endl;
       cout<<w->getName()<<". Health: "<<w->getHealth()<<". "<<w->getMovement()<<" Positioned at "<<w->getPosition()<<". "<<w->getName()<<" is shooting "<<w->getShoottype()<<"."<<endl;
       if(mask)
       {
            if(e->getPosition()-w->getPosition()<=w->getRange())
                e->roundType(choice);
            cout<<"EnemyTower's Health : "<<e->getHealth()<<". EnemyTower is shooting "<<e->getShoottype()<<"."<<endl;

            //flag=0;
       }
       do
       {
           if(e->getHealth()<=0)
           {
               cout<<"Game Over!! You Won!!"<<endl;
               return 0;
           }

           w->roundType(choice);


           cout<<"Round : "<<i++<<endl;
           if(w->getHealth()>0)
           {
               if(e->getPosition()-w->getPosition()<=w->getRange())
                    e->roundType(choice);
               cout<<w->getName()<<". Health: "<<w->getHealth()<<". "<<w->getMovement()<<" Positioned at "<<w->getPosition()<<". "<<w->getName()<<" is shooting "<<w->getShoottype()<<"."<<endl;
               if(e->getHealth()>0)
               {
                      cout<<"EnemyTower's Health : "<<e->getHealth()<<". EnemyTower is shooting "<<e->getShoottype()<<"."<<endl;
                }
               else cout<<endl;
           }
           else
           {
               cout<<w->getName()<<". Health: "<<w->getHealth()<<". Unit Died!!"<<endl;
               break;
           }
       }while(w->getHealth()>=0);

       e->cost_update(choice);
       if(e->getCost()<100)
       {
           cout<<"Game Over!!You are out of money!!"<<endl;
           return 0;
       }
    }

        ///You have to complete all the functionalities of the user using the base class pointer w.
        ///That means you have to call the derived class functions using only this.
    return 0;
    }
