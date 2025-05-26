#include<iostream>



class Player{
    protected:
        std::string name;
        int hp;
        int mp;
        int attack;

        

    public:

    Player(std::string name){
        
        this->name = name;
        this->hp = 100;
        this->mp = 1;
        this->attack = 10;
    }

    bool isAlive(){
        return hp > 0;
    }

    std::string getName(){
        return name;
    }

    int getHp(){
        return hp;
    }

    int getMp(){
        return mp;
    }

    int getAttack(){
        return attack;
    }

};

class Warrior : public Player{
    public: 
        Warrior(std::string name) : Player(name){
            hp = 150;
            mp = 20;
            attack = 45;
        }
};

class Mage : public Player{
    public: 
        Mage(std::string name) : Player(name){
            hp = 70;
            mp = 120;
            attack = 30;
        }
};

class Archer : public Player{
    public: 
        Archer(std::string name) : Player(name){
            hp = 100;
            mp = 60;
            attack = 35;
        }
};




class Game{
    public:
    std::string name;
    std::string gameClass;
    Player* player = nullptr;

    Game(){
        

    }


    void getName(){
        std::cout<<"Привет...игрок?Напишы свое имя:\n";
        std::getline(std::cin, name);

    }

    void greet(){
        std::cout << "Хммм... " << name << ", ты новенький?\n";
        std::cout << "В любом случае, добро пожаловать в нашу деревню.\n";
        std::cout << "Да, она маленькая, но для тебя уже есть задание.\n";
        std::cout << "Получено задание: убить 5 гоблинов.\n";
    }

    void getClass(){


        std::cout<<"\nА да...Выбери себе один из 3 классов\n";
        std::cout<<"На выбор: Войн,Маг,Лучник\n";
        
        
        std::getline(std::cin, gameClass);

        if(gameClass == "Войн"){
            player = new Warrior(name);
        }else if(gameClass == "Маг"){
            player = new Mage(name);
        }else if(gameClass == "Лучник"){
            player = new Archer(name);
        }else{
            std::cout<<"Упсс, проблемка...Магический кристал не нашол для вас классов.Возможно теперь вы навсегда обычний человек...\n";

            return;
        }
    
    }


    void introArt() {
        std::cout << "============================\n";
        std::cout << " ДОБРО ПОЖАЛОВАТЬ В RPG v0.1   \n";
        std::cout << "============================\n\n";
    }

    void menu(){
        std::cout<<"1. Искать приключений на свой меч!\n";
        std::cout<<"2. Посмотреть статистику\n";
        std::cout<<"3. Выйти из игры\n";
    }

    

    void showStats(){
            if(player == nullptr){
            std::cout<<"Коллапс магического кристала!!!:#@@1@#\n";
            return;
        }


        std::cout<<"\n===========================================\n";

        std::cout<<"Ваша статистика:\n";
        std::cout<<"Ваше имя:"<<name<<"\n";
        std::cout<<"Вы выбрали класс:"<<gameClass<<"\n";
        std::cout<<"HP: "<<player->getHp()<<" \n";
        std::cout<<"MP: "<<player->getMp()<<" \n";
        std::cout<<"Ваш урон: "<<player->getAttack()<<"\n";

        std::cout<<"\n===========================================\n";
        
        }

    



};



int main(){
    
    Game game;
    game.introArt();
    game.getName();
    game.greet();
    game.getClass();
    int op;

    do{

    std::cin>>op;
    game.menu();

    switch(op){
        case 1:
        std::cout<<"Я коносубу смотрю мне не до этого\n";

        break;

        case 2:
        game.showStats();

        break;

        case 3:
        std::cout<<"Уже уходишь?...Ты меня разочаровал...Приходи еще!\n";

        break;

        default:
        std::cout<<"Нет такой команды!\n";
    }

    }while(op !=3);



    return 0;
}
