#include <SFML/Graphics.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <windows.h>

#include "../src/game15_logic/game15_logic.hpp"

const char* IMAGE
        = "../external/images/image.jpg"; // Путь к картинке заднего фона
const char* FONT = "../external/images/PakenhamBl_Italic.ttf"; // Путь к шрифту
const char* YOUWIN = "../external/images/YouWinTexture.jpg"; // Путь к текстуре
                                                             // "Ты Выиграл!"
int BlockSize = 100; // Размер блока
int WIGHT = 1800;    // Ширина окна
int HEIGHT = 900;    // Высота окна
int NewGame_Size = 50, NewGame_X = 100, NewGame_Y = 200; // "Новая Игра"
int TableRecords_Size = 50, TableRecords_X = 100,
    TableRecords_Y = 300; //  "Таблица Рекордов"
int Exit_Size = 50, Exit_X = 100, Exit_Y = 400;    // "Выход"
int About_Size = 50, About_X = 100, About_Y = 800; // "О Создателях"
int Easy_Size = 50, Easy_X = 100, Easy_Y = 200;    // "Легкий"
int Normal_Size = 50, Normal_X = 100, Normal_Y = 200; // "Средний"
int Hard_Size = 50, Hard_X = 100, Hard_Y = 200;       // "Тяжелый"
int Field_Size = 50, Field_X = 100, Field_Y = 200; // Поле для Ввода

// Выводит сообщение о победе
void YouWin(sf::RenderWindow& window)
{
    sf::Texture YouWinTexture;
    bool f = YouWinTexture.loadFromFile(YOUWIN);
    sf::Sprite YouWin(YouWinTexture);
    YouWin.setScale(3.0f, 3.0f);
    YouWin.setPosition(WIGHT / 2 - 300, HEIGHT / 2 - 300);
    window.draw(YouWin);
    window.display();
    Sleep(1500);
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
// Инициализация главного меню
int MainMenu(
        sf::RenderWindow& window,
        sf::Sprite background,
        sf::Font font,
        RecordsTable Table)
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

    sf::Text about("The Game was created \n by one stogle", font, 50);
    about.setPosition(500, 400);

    int diff;
    int count;
    std::string name;
    bool isMenu = 1;
    int menuNum = 0;
    Record NewRecord;

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
                diff = Difficulty(window, font, background);
                if (diff == 0)
                    continue;
                name = EnterTheName(window, background, font);
                if (name == "0")
                    continue;
                count
                        = Game(name,
                               diff,
                               BlockSize,
                               (WIGHT / 2) - BlockSize * diff / 2,
                               (HEIGHT / 2) - BlockSize * diff / 2,
                               1000,
                               window,
                               background,
                               font);
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
