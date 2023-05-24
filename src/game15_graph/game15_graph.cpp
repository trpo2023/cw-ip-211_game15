#include <SFML/Graphics.hpp>

#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <windows.h>

#include "../game15_logic/game15_logic.h"

const char* YOUWIN = "../external/images/YouWinTexture.jpg"; // Путь к текстуре

void YouWin(sf::RenderWindow& window)
{
    sf::Texture YouWinTexture;
    YouWinTexture.loadFromFile(YOUWIN);
    sf::Sprite YouWin(YouWinTexture);
    YouWin.setScale(3.0f, 3.0f);
    YouWin.setPosition(WIGHT / 2 - 300, HEIGHT / 2 - 300);
    window.draw(YouWin);
    window.display();
    Sleep(1500);
}

struct Record {
    std::string name;  // Имя игрока
    std::string score; // Счет игрока
    std::string turns; // Потраченное количество ходов
    std::string difficly; // Сложность игры
};

// Все сохраненные рекорды
struct RecordsTable {
    std::vector<Record> records;
    // Метод создания новой записи
    void addRecord(Record record)
    {
        records.push_back(record);
        Record temp;
        // Сортируем результаты по счету
        for (int i = 0; i < records.size(); i++)
            for (int j = i + 1; j < records.size(); j++)
                if (records[i].score < records[j].score) {
                    temp = records[i];
                    records[i] = records[j];
                    records[j] = temp;
                }
        // Если количество результатов больше 10 - то удаляем последний
        if (records.size() > 10)
            records.pop_back();
    }
    // Сохранение таблицы в файле
    void saveTableToFile()
    {
        // Открываем или создаем файл "records.txt"
        std::ofstream file;
        file.open("../data/records.txt");
        // Записываем в него все рекорды
        for (int i = 0; i < records.size(); i++) {
            if ((records[i].turns) == "0")
                continue;
            file << records[i].name << "/" << records[i].turns << "/"
                 << records[i].score << "/" << records[i].difficly << std::endl;
        }
        // Закрываем файл
        file.close();
    }
    // Загрузка таблицы из файла
    int loadTableFromFile()
    {
        // Открывает файл "records.txt"
        std::ifstream file;
        file.open("../data/records.txt");
        if (!file.is_open())
            return 1;
        // Записывает данные из файла в структуру
        std::string line;
        while (getline(file, line)) {
            Record record;
            size_t pos = 0;
            pos = line.find("/");
            record.name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("/");
            record.turns = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("/");
            record.score = line.substr(0, pos);
            line.erase(0, pos + 1);
            record.difficly = line;
            addRecord(record);
        }
        // Закрытие файла
        file.close();
        return 0;
    }
};
// Вывод Таблицу рекордов из файла
void PrintRecord(sf::RenderWindow& window, sf::Font font)
{
    std::ifstream file("../data/records.txt");
    std::string content;
    bool isRec = true;
    content += "Name Turns Score Difficulty\n";
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            content += line + "\n";
        }
        file.close();
    }
    sf::Text text(content, font, 40);
    text.setPosition(10, 100);

    if (isRec) {
        window.draw(text);
        window.display();
        while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            ;
    }
}

// Возвращает значение сложности полученное от игрока
int Difficulty(sf::RenderWindow& window, sf::Font font, sf::Sprite background)
{
    // Создаем кнопки
    sf::Text Easy("Easy", font, 40);
    Easy.setFillColor(sf::Color::White);
    Easy.setPosition(50, 50);

    sf::Text Normal("Normal", font, 40);
    Normal.setFillColor(sf::Color::White);
    Normal.setPosition(50, 150);

    sf::Text Hard("Hard", font, 40);
    Hard.setFillColor(sf::Color::White);
    Hard.setPosition(50, 250);

    // Отображаем кнопки на экране
    window.draw(background);
    window.draw(Easy);
    window.draw(Normal);
    window.draw(Hard);
    window.display();

    // Обрабатываем события до тех пор, пока пользователь не выберет сложность
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Escape)
                return 0;
            else if (event.type == sf::Event::MouseButtonPressed) {
                // Проверяем на какую кнопку нажал пользователь
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition
                            = window.mapPixelToCoords(sf::Vector2i(
                                    event.mouseButton.x, event.mouseButton.y));
                    if (Easy.getGlobalBounds().contains(mousePosition)) {
                        return 2;
                    } else if (Normal.getGlobalBounds().contains(
                                       mousePosition)) {
                        return 3;
                    } else if (Hard.getGlobalBounds().contains(mousePosition)) {
                        return 4;
                    }
                }
            }
        }
    }
}
// Отрисовывает таблицу рекордов в главном окне
void DrawRecords(
        sf::RenderWindow& window,
        sf::Sprite background,
        sf::Font font,
        sf::Text about)
{
    window.draw(background);
    PrintRecord(window, font);
    window.draw(about);
    window.display();
    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        ;
}
std::string
EnterTheName(sf::RenderWindow& window, sf::Sprite background, sf::Font font)
{
    sf::RectangleShape Field;
    Field.setFillColor(sf::Color::Black);
    Field.setSize(sf::Vector2f(500, 60));
    Field.setPosition(625, 405);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setPosition(660, 400);

    // Кнопка
    sf::Text EnterTheName;
    EnterTheName.setFont(font);
    EnterTheName.setString("Enter The Name");
    EnterTheName.setFillColor(sf::Color::White);
    EnterTheName.setPosition(WIGHT / 2 - 200, 100);
    EnterTheName.setCharacterSize(50);

    std::string input;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Escape)
                return "0";
            else if (
                    event.key.code == sf::Keyboard::Enter
                    && input.size() > 0) // Enter
                return input;
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) // check if input is ASCII
                {
                    if (event.text.unicode == '\b'
                        && input.size() > 0) // backspace
                    {
                        input.pop_back();
                    }

                    else if (event.text.unicode != '\b' && input.size() < 20) {
                        input += static_cast<char>(event.text.unicode);
                    }
                    text.setString(input);
                }
            }
        }

        window.draw(background);
        window.draw(Field);
        window.draw(text);
        window.draw(EnterTheName);
        window.display();
    }

    return input;
}
int MainMenu(sf::RenderWindow& window, sf::Sprite background, sf::Font font)
{
    sf::Text NewGame("New Game", font, NewGame_Size);
    NewGame.setPosition(NewGame_X, NewGame_Y);

    sf::Text TableRecords("Scoreboard", font, TableRecords_Size);
    TableRecords.setPosition(
            TableRecords_X, TableRecords_Y); // Кнопка "Таблица рекордов"

    sf::Text Exit("Exit", font, Exit_Size);
    Exit.setPosition(Exit_X, Exit_Y); // Кнопка "Выход"

    sf::Text About("About", font, About_Size);
    About.setPosition(About_X, About_Y); // Кнопка "О создателях"

    sf::Text about("The Game was created \n by two stogles", font, 50);
    about.setPosition(500, 400);

    int diff;
    int count;
    std::string name;
    bool isMenu = 1;
    int menuNum = 0;
    Record NewRecord;
    RecordsTable Table;

    while (isMenu && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        menuNum = 0;

        window.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(100, 200, 300, 200)
                    .contains(sf::Mouse::getPosition(window)))
            menuNum = 1; // Начать игру
        if (sf::IntRect(100, 300, 300, 200)
                    .contains(sf::Mouse::getPosition(window)))
            menuNum = 2; // Таблица рекордов
        if (sf::IntRect(100, 400, 300, 200)
                    .contains(sf::Mouse::getPosition(window)))
            menuNum = 3; // Выход
        if (sf::IntRect(100, 800, 300, 200)
                    .contains(sf::Mouse::getPosition(window)))
            menuNum = 4; // О создателях

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (menuNum == 1) {
                bool win = false;
                diff = Difficulty(window, font, background);
                if (diff == 0)
                    continue;
                name = EnterTheName(window, background, font);
                if (name == "0")
                    continue;
                count
                        = Game(diff,
                               BlockSize,
                               (WIGHT / 2) - BlockSize * diff / 2,
                               (HEIGHT / 2) - BlockSize * diff / 2,
                               window,
                               background,
                               font,
                               win);
                if (win)
                    YouWin(window);
                NewRecord.name = name;
                NewRecord.score
                        = std::to_string(diff * diff * 500 - count * 10);
                NewRecord.turns = std::to_string(count);
                if (diff == 2)
                    NewRecord.difficly = "Easy";
                if (diff == 3)
                    NewRecord.difficly = "Normal";
                if (diff == 4)
                    NewRecord.difficly = "Hard";
                Table.addRecord(NewRecord);
                Table.saveTableToFile();
            }
            if (menuNum == 2) {
                DrawRecords(window, background, font, about);
                window.display();
                while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    ;
            }
            if (menuNum == 3) {
                isMenu = false;
            }
            if (menuNum == 4) {
                window.draw(background);
                window.draw(about);
                window.display();
                while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    ;
            }
        }

        window.draw(background);
        window.draw(NewGame);
        window.draw(TableRecords);
        window.draw(Exit);
        window.draw(About);
        window.display();
    }
    return 0;
}
