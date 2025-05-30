#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <ctime>

class Map {
private:
    static const int HEIGHT = 5;
    static const int WIDTH = 10;
    char matrix[HEIGHT][WIDTH];
    int PlayerX;
    int PlayerY;
    int monstrX[5];
    int monstrY[5];
    bool monstrAlive[5]; 

public:
    Map() {
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                matrix[i][j] = '.';
            }
        }

        PlayerX = 1;
        PlayerY = 1;
        matrix[PlayerY][PlayerX] = 'P';

        for(int i = 0; i < 5; i++) {
            monstrAlive[i] = false;
        }
    }

    void movePlayer(std::string command) {
        if (command.length() > 2) {
            std::cout << "Слишком много букав!\n";
            return;
        }

        int newPlayerX = PlayerX;
        int newPlayerY = PlayerY;

        if (command == "w" && newPlayerY > 0) newPlayerY--;
        else if (command == "s" && newPlayerY < HEIGHT - 1) newPlayerY++;
        else if (command == "d" && newPlayerX < WIDTH - 1) newPlayerX++;
        else if (command == "a" && newPlayerX > 0) newPlayerX--;
        else {
            std::cout << "Нет такой команды!\n";
            return;
        }

        matrix[PlayerY][PlayerX] = '.';
        PlayerX = newPlayerX;
        PlayerY = newPlayerY;
        matrix[PlayerY][PlayerX] = 'P';
    }

    void displayMap() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if(matrix[i][j] == 'M') {
                    matrix[i][j] = '.';
                }
            }
        }
        
        matrix[PlayerY][PlayerX] = 'P';
        
        for(int k = 0; k < 5; k++) {
            if(monstrAlive[k]) {
                matrix[monstrY[k]][monstrX[k]] = 'M';
            }
        }
        
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                std::cout << matrix[i][j];
            }
            std::cout << std::endl;
        }
    }

    void createMonster() {
        for (int k = 0; k < 5; k++) {
            int x, y;
            bool valid;

            do {
                x = rand() % WIDTH;
                y = rand() % HEIGHT;
                valid = true;

                if (x == PlayerX && y == PlayerY) {
                    valid = false;
                    continue;
                }

                for (int j = 0; j < k; j++) {
                    if (x == monstrX[j] && y == monstrY[j]) {
                        valid = false;
                        break;
                    }
                }

            } while (!valid);

            monstrX[k] = x;
            monstrY[k] = y;
            monstrAlive[k] = true;
            matrix[y][x] = 'M';
        }
    }

    int isFight(int x, int y){
        for(int i = 0; i < 5; i++){
            if(monstrX[i] == x && monstrY[i] == y && monstrAlive[i]) {
                return i;
            }
        }
        return -1;
    }

    void killMonster(int index) {
        if(index >= 0 && index < 5) {
            monstrAlive[index] = false;
        }
    }

    bool allMonstersKilled() {
        for(int i = 0; i < 5; i++) {
            if(monstrAlive[i]) {
                return false;
            }
        }
        return true;
    }

    int getX(){
        return PlayerX;
    }
    int getY(){
        return PlayerY;
    }

    void clearMap() {
        std::system("clear");
    }
};

class Monstr {
private:
    std::string name;
    int hp;
    int attack;

public:
    Monstr() {
        this->name = "Гоблин";
        this->hp = 100;
        this->attack = rand() % 25 + 1;
    }

    bool isAlive() {
        return hp > 0;
    }

    std::string getName() {
        return name;
    }

    int getHp() {
        return hp;
    }

    int getAttack() {
        return attack;
    }

    void takeDamage(int dmg) {
        hp -= dmg;
        if (hp < 0) hp = 0;
    }
};

class Player {
protected:
    std::string name;
    int hp;
    int mp;
    int attack;

public:
    Player(std::string name) {
        this->name = name;
        this->hp = 100;
        this->mp = 1;
        this->attack = 10;
    }

    virtual ~Player(){
        
    }

    bool isAlive() {
        return hp > 0;
    }

    std::string getName() {
        return name;
    }

    int getHp() {
        return hp;
    }

    int getMp() {
        return mp;
    }

    int getAttack() {
        return attack;
    }

    void takeDamage(int dmg) {
        hp -= dmg;
        if (hp < 0) hp = 0;
        std::cout << "Вы получили " << dmg << " урона\n";
    }
};

class Warrior : public Player {
public:
    Warrior(std::string name) : Player(name) {
        hp = 150;
        mp = 20;
        attack = 45;
    }
    
    bool useSkillwarrior(Monstr &monstr){
        if(mp < 20){
            return false;
        }
        
        mp-=20;
        int skill_damageWarrior = attack+20;
        monstr.takeDamage(skill_damageWarrior);
       
        return true;
    }
};

class Mage : public Player {
public:
    Mage(std::string name) : Player(name) {
        hp = 70;
        mp = 120;
        attack = 30;
    }

    bool useSkillMage(Monstr &monstr){
        if(mp < 50){
            return false;
        }
        
        mp-=50;
        int skill_damageMage = attack*2;
        monstr.takeDamage(skill_damageMage);
        
        return true;
    }
};

class Archer : public Player {
public:
    Archer(std::string name) : Player(name) {
        hp = 100;
        mp = 60;
        attack = 35;
    }

    bool useSkillArcher(Monstr &monstr){
        if(mp < 30){
            return false;
        }

        mp-=30;
        int skill_damageArcher = attack*1.5;
        monstr.takeDamage(skill_damageArcher);

        return true;
    }
};

class Megumin : public Player {
public:
    Megumin(std::string name) : Player(name) {
        hp = 100;
        mp = 10;
        attack = 1;
    }

    bool useSkillMegumin(Monstr &monstr){
        if(mp < 5){
            return false;
        }

        mp-=5;
        int skill_damageMegumin = 1000;
        monstr.takeDamage(skill_damageMegumin);
        
        return true;
    }
};

class Game {
public:
    std::string name;
    std::string gameClass;
    Player* player = nullptr;
    int monstersKilled = 0; 

    Game() {}

    void getName() {
        std::cout << "Привет... игрок? Напиши своё имя:\n";
        std::getline(std::cin, name);
    }

    void greet() {
        std::cout << "Хммм... " << name << ", ты новенький?\n";
        std::cout << "В любом случае, добро пожаловать в нашу деревню.\n";
        std::cout << "Да, она маленькая, но для тебя уже есть задание.\n";
        std::cout << "Получено задание: убить 5 гоблинов.\n";
    }

    void getClass() {
        std::cout << "\nА, да... Выбери себе один из 3 классов\n";
        std::cout << "На выбор: Воин, Маг, Лучник\n";

        std::getline(std::cin, gameClass);

        if (gameClass == "Воин") {
            player = new Warrior(name);
        } else if (gameClass == "Маг") {
            player = new Mage(name);
        } else if (gameClass == "Лучник") {
            player = new Archer(name);
        } else if (gameClass == "Мегумин") {
            name = "Мегумин";
            gameClass = "Архи Маг";
            player = new Megumin(name);
            std::cout << "Да ты нашёл меня... ТЫ ПРОБУДИЛ ДРЕВНЕГО МАГА МЕГУМИН!!! Я САМЫЙ ЛУЧШИЙ АРХИ МАГ ХАХАХАХАХАХАХА!!!\n";
        } else {
            std::cout << "Упсс, проблемка... Магический кристалл не нашёл для вас классов. Возможно, теперь вы навсегда обычный человек...\n";
            return;
        }
    }

    void introArt() {
        std::cout << "============================\n";
        std::cout << " ДОБРО ПОЖАЛОВАТЬ В RPG v0.9\n";
        std::cout << "============================\n\n";
    }

    void menu() {
        std::cout << "1. Искать приключений на свой меч!\n";
        std::cout << "2. Посмотреть статистику\n";
        std::cout << "3. Выйти из игры\n";
    }

    void showStats() {
        if (player == nullptr) {
            std::cout << "Коллапс магического кристалла!!!:#@@1@#\n";
            return;
        }

        std::cout << "\n===========================================\n";
        std::cout << "Ваша статистика:\n";
        std::cout << "Ваше имя: " << name << "\n";
        std::cout << "Вы выбрали класс: " << gameClass << "\n";
        std::cout << "HP: " << player->getHp() << " \n";
        std::cout << "MP: " << player->getMp() << " \n";
        std::cout << "Ваш урон: " << player->getAttack() << "\n";
        std::cout << "Убито монстров: " << monstersKilled << "/5\n";
        std::cout << "===========================================\n";
    }

    bool fight(Player *player, Monstr &monstr, std::string gameClass){
        std::cout<<"Вы столкнулись с "<<monstr.getName()<<"\n";
        while(player->isAlive() && monstr.isAlive()){
            std::cout<<"Ваше HP: "<<player->getHp()<<"\n";
            std::cout<<"HP врага: "<<monstr.getHp()<<"\n";

            std::cout<<"1.Базовая аттака\n";
            std::cout<<"2.Использовать навык\n";
            std::cout<<"3.Бежать с позором\n";
            int fight_choice;
            std::cin>>fight_choice;

            switch(fight_choice){
    case 1: {
        int player_dmg = player->getAttack();
        std::cout << player->getName() << " атакует и наносит " << player_dmg << " урона!\n";
        monstr.takeDamage(player_dmg);
        std::cout << "HP " << monstr.getName() << ": " << monstr.getHp() << "\n";
        break;
    }

    case 2: {
        if (gameClass == "Воин") {
            Warrior* w = dynamic_cast<Warrior*>(player);
            if (w && w->useSkillwarrior(monstr)) {
                std::cout << "Вы использовали мощный удар Воина!\n";
            } else {
                std::cout << "Недостаточно маны!\n";
            }
        } else if (gameClass == "Маг") {
            Mage* m = dynamic_cast<Mage*>(player);
            if (m && m->useSkillMage(monstr)) {
                std::cout << "Вы призвали магический шар!\n";
            } else {
                std::cout << "Недостаточно маны!\n";
            }
        } else if (gameClass == "Лучник") {
            Archer* a = dynamic_cast<Archer*>(player);
            if (a && a->useSkillArcher(monstr)) {
                std::cout << "Вы выстрелили 3 раза!\n";
            } else {
                std::cout << "Недостаточно маны!\n";
            }
        } else if (gameClass == "Архи Маг") {
            Megumin* me = dynamic_cast<Megumin*>(player);
            if (me && me->useSkillMegumin(monstr)) {
                std::cout << "ВЗРЫВ!!! МАГИЯ ВЗРЫВА МЕГУМИН!!! *БАБАХ*\n";
            } else {
                std::cout << "Недостаточно маны!\n";
            }
        }
        break;
    }

    case 3: {
        std::cout << "Позор...\n";
        return false;
    }

    default: {
        std::cout << "Нет такой команды!\n";
        break;
    }
}

            if(monstr.isAlive()) {
                int monstr_dmg = monstr.getAttack();
                std::cout<<"Монстр атакует вас и наносит "<<monstr_dmg<<" урона!"<<"\n";
                player->takeDamage(monstr_dmg);
                std::cout<<"HP "<<player->getName()<<": "<<player->getHp()<<"\n";
            }
        }
        
        if(!monstr.isAlive()) {
            std::cout << "Вы победили " << monstr.getName() << "!\n";
            monstersKilled++;
            return true; 
        }
        
        return false; 
    }
};

int main() {
    srand(time(NULL));

    Game game;
    Map map;

    game.introArt();
    game.getName();
    game.greet();
    game.getClass();

    int op;
    std::string c;

    do {
        game.menu();
        std::cin >> op;
        std::cin.ignore();

        switch (op) {
        case 1:
            map.createMonster();
            map.displayMap();

            while (true) {
                std::cout << "Введите команду (w/a/s/d), q для выхода\n";
                std::cin >> c;
                if (c == "q") break;

                map.movePlayer(c);
                int monsterIndex = map.isFight(map.getX(), map.getY());
                if(monsterIndex != -1){
                    Monstr currentMonster; 
                    bool monsterDefeated = game.fight(game.player, currentMonster, game.gameClass);
                    
                    if(!game.player->isAlive()){
                        std::cout<<"Вы погибли героической смертью...<END>\n";
                        return 0;
                    }
                    
                    if(monsterDefeated) {
                        map.killMonster(monsterIndex);

                        if(map.allMonstersKilled()) {
                            std::cout << "\n=== ПОЗДРАВЛЯЕМ! ===\n";
                            std::cout << "Вы выполнили квест и убили всех 5 гоблинов!\n";
                            std::cout << "Деревня в безопасности!\n";
                            std::cout << "==================\n";
                            break;
                        }
                    }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(800));
                map.clearMap();
                map.displayMap();
            }
            break;

        case 2:
            game.showStats();
            break;

        case 3:
            std::cout << "\nУже уходишь?.. Ты меня разочаровал... Приходи ещё!\n";
            delete game.player;
            break;

        default:
            std::cout << "\nНет такой команды!\n";
        }

    } while (op != 3);

    return 0;
}
