
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Базовый класс животных
class Animal {
public:
    Animal(string name, int age, string habitat) : name_(name), age_(age), habitat_(habitat) {}

    // Общие методы
    void eat() {
        cout << name_ << " is eating." << endl;
    }

    void sleep() {
        cout << name_ << " is sleeping." << endl;
    }

    virtual void move() {
        cout << name_ << " is moving." << endl;
    }

    // Метод для кормления
    void feed(string food) {
        cout << name_ << " is eating " << food << "." << endl;
    }

    // Общие свойства
    string name_;
    int age_;
    string habitat_;
};

// Класс рыб
class Fish : public Animal {
public:
    Fish(string name, int age, string habitat, bool isSaltwater, bool isViviparous) : Animal(name, age, habitat), isSaltwater_(isSaltwater), isViviparous_(isViviparous) {}

    // Уникальный метод
    void swim() {
        cout << name_ << " is swimming." << endl;
    }

    // Переопределенный метод
    void move() override {
        cout << name_ << " is swimming. ";
        if (isViviparous_) {
            cout << name_ << " it is viviparous." << endl;
        }
        else {
            cout << name_ << " it lays eggs." << endl;
        }
    }

    // Уникальное свойство
    bool isSaltwater_;
    bool isViviparous_;
};

// Класс птиц
class Bird : public Animal {
public:
    Bird(string name, int age, string habitat, bool canFly, bool canSing) : Animal(name, age, habitat), canFly_(canFly), canSing_(canSing) {}

    // Уникальный     
    void fly() {
        if (canFly_) {
            cout << name_ << " can fly." << endl;
        }
        else {
            cout << name_ << " cannot fly." << endl;
        }
    }

    // Переопределенный метод
    void move() override {
        cout << name_ << " is flying." << endl;
        if (canSing_) {
            cout << name_ << " can sing." << endl;
        }
        else {
            cout << name_ << " cannot sing." << endl;
        }
    }

    // Уникальное свойство
    bool canFly_;
    bool canSing_;
};

// Класс млекопитающих
class Mammal : public Animal {
public:
    Mammal(string name, int age, string habitat, bool hasFur, bool isCarnivore) : Animal(name, age, habitat), hasFur_(hasFur), isCarnivore_(isCarnivore) {}

    // Уникальный метод
    void nurse() {
        cout << name_ << " is nursing its young." << endl;
    }

    // Уникальное свойство
    bool hasFur_;
    bool isCarnivore_;
};

// Функция для добавления животных
void addAnimal(vector<Animal*>& animals) {
    string name, habitat;
    int age;
    char type;
    cout << "Zoo\n\n";

    cout << "Enter the name of the animal: ";
    cin >> name;

    cout << "Enter the age of the animal: ";
    cin >> age;

    cout << "Enter the habitat of the animal: ";
    cin >> habitat;

    cout << "Enter the type of the animal (F for fish, B for bird, M for mammal): ";
    cin >> type;

    if (type == 'F') {
        bool isSaltwater;
        cout << "Is the fish saltwater (Y/N)? ";
        char saltwater;
        cin >> saltwater;
        isSaltwater = (saltwater == 'Y');
        bool isViviparous;
        cout << "Does the fish give birth to live young (Y/N)? ";
        char viviparous;
        cin >> viviparous;
        isViviparous = (viviparous == 'Y');


        animals.push_back(new Fish(name, age, habitat, isSaltwater, isViviparous));
    }
    else if (type == 'B') {
        bool canFly;
        cout << "Can the bird fly (Y/N)? ";
        char fly;
        cin >> fly;
        canFly = (fly == 'Y');
        bool canSing;
        cout << "Can the bird sing (Y/N)? ";
        char sing;
        cin >> sing;
        canSing = (sing == 'Y');
        animals.push_back(new Bird(name, age, habitat, canFly, canSing));
    }
    else if (type == 'M') {
        bool hasFur, isCarnivore;
        cout << "Does the mammal have fur (Y/N)? ";
        char fur;
        cin >> fur;
        hasFur = (fur == 'Y');
        cout << "Is the mammal a carnivore (Y/N)? ";
        char carnivore;
        cin >> carnivore;
        isCarnivore = (carnivore == 'Y');
        animals.push_back(new Mammal(name, age, habitat, hasFur, isCarnivore));
    }
    else {
        cout << "Invalid animal type." << endl;
    }
}

int main() {
    // Создаем по 3 объекта каждого класса
    vector<Animal*> animals;
    animals.push_back(new Fish("Salmon", 2, "River", false, false));
    animals.push_back(new Fish("Tuna", 5, "Ocean", true, false));
    animals.push_back(new Fish("Clownfish", 1, "Coral Reef", true, true));

    animals.push_back(new Bird("Eagle", 10, "Mountains", true, false));
    animals.push_back(new Bird("Penguin", 3, "Antarctica", false, false));
    animals.push_back(new Bird("Ostrich", 7, "Savannah", true, true));

    animals.push_back(new Mammal("Lion", 8, "Savannah", true, true));
    animals.push_back(new Mammal("Dolphin", 4, "Ocean", false, true));
    animals.push_back(new Mammal("Kangaroo", 6, "Australia", true, false));


    // Добавляем новых животных в каждый класс
    addAnimal(animals);
    addAnimal(animals);
    addAnimal(animals);


    // Вызываем методы для каждого животного
    for (Animal* animal : animals) {
        animal->eat();
        animal->sleep();
        animal->move();

        // Вызываем уникальные методы для каждого класса
        Fish* fish = dynamic_cast<Fish*>(animal);
        if (fish != nullptr) {
            fish->swim();
        }

        Bird* bird = dynamic_cast<Bird*>(animal);
        if (bird != nullptr) {
            bird->fly();
        }

        Mammal* mammal = dynamic_cast<Mammal*>(animal);
        if (mammal != nullptr) {
            mammal->nurse();
            if (mammal->isCarnivore_) {
                cout << mammal->name_ << " hunts." << endl;
            }
            else {
                cout << mammal->name_ << " is looking for plants." << endl;
            }
        }

        cout << endl;
    }

    // Поддержка кормления выбранного животного
    cout << "Select an animal to feed: ";
    string selectedAnimal;
    cin >> selectedAnimal;

    cout << "Select the food to feed the animal: ";
    string selectedFood;
    cin >> selectedFood;


    // Находим выбранное животное и кормим его выбранным кормом
    for (Animal* animal : animals) {
        if (animal->name_ == selectedAnimal) {
            animal->feed(selectedFood);
            break;
        }
    }

    // Запрашиваем у пользователя, хочет ли он продолжить
    cout << "Do you want to continue (Y/N)? ";
    char continueOption;
    cin >> continueOption;

    if (continueOption == 'Y') {
        // Восстанавливаем программу после выбора кормления
        main();
    }
    else {
        // Закрытие программы
        exit(0);
    }


    // Освобождаем память
    for (Animal* animal : animals) {
        delete animal;
    }

    return 0;
}