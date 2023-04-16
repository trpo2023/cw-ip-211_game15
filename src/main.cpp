#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace sf;
using namespace std;

// Структура для хранения данных о пользователе и его рекорде
struct Record
{
    string name;
    double money;
    string date;
};

// Структура для хранения таблицы рекордов
struct RecordsTable
{
    vector<Record> records;

    // Функция для добавления новой записи
    void addRecord(Record record)
    {
        records.push_back(record);
    }

    // Функция для вывода всей таблицы рекордов на экран
    void printTable()
    {
        for (int i = 0; i < records.size(); i++)
        {
            cout << "Name: " << records[i].name << " Money: " << records[i].money << " Date: " << records[i].date << endl;
        }
    }

    // Функция для сохранения таблицы рекордов в файл
    void saveTableToFile(string fileName)
    {
        ofstream file;
        file.open(fileName);

        for (int i = 0; i < records.size(); i++)
        {
            file << records[i].name << " " << records[i].date << " " << records[i].money << endl;
        }

        file.close();
    }

    // Функция для загрузки таблицы рекордов из файла
    void loadTableFromFile(string fileName)
    {
        ifstream file;
        file.open("records.txt");

        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                Record record;

                // Разбиваем строку на отдельные значения и сохраняем их в структуру
                size_t pos = 0;
                pos = line.find(" ");
                record.name = line.substr(0, pos);
                line.erase(0, pos + 1);
                pos = line.find(" ");
                record.money = stod(line.substr(0, pos));
                line.erase(0, pos + 1);
                record.date = line;

                addRecord(record);
            }
            file.close();
        }
    }
};

void print_record(RenderWindow& window) {
    // Открываем файл для чтения
    ifstream file("records.txt");
    string content;
    Font font;
    bool isRec = true;
    if (!font.loadFromFile("images/PakenhamBl_Italic.ttf"))
    {
        // Обработка ошибки, если шрифт не удалось загрузить
    }
    // Если файл запущен успешно
    if (file.is_open())
    {
        // Считываем содержимое файла в строку
        string line;
        while (getline(file, line))
        {
            content += line + "\n";
        }
        file.close();
    }

    Text text(content, font, 40);
    text.setPosition(10, 100); // Позиция текста

    // Основной цикл приложения
    if(isRec)
    {
        // Отрисовка текста
        window.draw(text);

        // Отображение созданного кадра
        window.display();
        while (!Keyboard::isKeyPressed(Keyboard::Escape));
    }
}

void mainMenu(RenderWindow& window)
{
    // Создаем фон для главного меню
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/img.png"))
    {
        // Обработка ошибки, если текстуру не удалось загрузить
    }
    Sprite background(backgroundTexture);

    // Создаем шрифт для текста на кнопках
    Font font;
    if (!font.loadFromFile("images/PakenhamBl_Italic.ttf"))
    {
        // Обработка ошибки, если шрифт не удалось загрузить
    }
    background.setPosition(-100, 0);

    // Создаем тексты для кнопок
    Text button1("New Game", font, 50);
    button1.setPosition(100, 200); // Установка позиции первой кнопки

    Text button2("Table Records", font, 50);
    button2.setPosition(100, 300); // Установка позиции второй кнопки

    Text button3("Exit", font, 50);
    button3.setPosition(100, 400); // Установка позиции третьей кнопки

    Text button4("About", font, 50);
    button4.setPosition(100, 800); // Установка позиции четвертой кнопки

    Text about("The Game was created \n by two stogles", font, 50);
    about.setPosition(500, 400);

    bool isMenu = 1;
    int menuNum = 0;

    while (isMenu)
    {
        menuNum = 0;

        window.clear(Color(129, 181, 221));

        if (IntRect(100, 200, 300, 200).contains(Mouse::getPosition(window))) menuNum = 1; 
        if (IntRect(100, 300, 300, 200).contains(Mouse::getPosition(window))) menuNum = 2; 
        if (IntRect(100, 400, 300, 200).contains(Mouse::getPosition(window))) menuNum = 3;
        if (IntRect(100, 800, 300, 200).contains(Mouse::getPosition(window))) menuNum = 4;

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
            if (menuNum == 2) { window.draw(background); print_record(window); window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
            if (menuNum == 3) { window.close(); isMenu = false; }
            if (menuNum == 4) { window.draw(background); window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }

        }

        window.draw(background);
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        window.draw(button4);

        window.display();
    }
    }
int main()
{

    RenderWindow window(sf::VideoMode(1600, 900), "GAME15");
    mainMenu(window);
    RecordsTable recordsTable;

    //// Пример добавления новой записи
    //Record rec;
    //int cont = 1;
    //while (cont == 1)
    //{
    //    cout << "Enter yout Nickname";
    //    cin >> rec.name;
    //    cout << endl;
    //    cout << "Enter yout Score";
    //    cin >> rec.money;
    //    cout << endl;
    //    time_t t = time(NULL);
    //    rec.date = __DATE__;
    //    recordsTable.addRecord(rec);
    //    cout << "continue? (1/0)";
    //    cin >> cont;
    //}

    //// Вывод всей таблицы рекордов на экран
    //recordsTable.printTable();

    //// Сохранение таблицы рекордов в файл
    //recordsTable.saveTableToFile("records.txt");

    //// Загрузка таблицы рекордов из файла
    //RecordsTable loadedRecordsTable;
    //loadedRecordsTable.loadTableFromFile("records.txt");

    //// Вывод загруженной таблицы на экран
    //loadedRecordsTable.printTable();
}