#include <SFML/Graphics.hpp>

#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <windows.h>

#include "../game15_logic/game15_logic.h"

const char* YOUWIN = "../external/images/YouWinTexture.jpg"; // Путь к текстуре

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

void Draw(
        Grid grid,
        sf::RenderWindow& window,
        sf::Font font,
        int blocksize,
        int vx,
        int vy)
{
    sf::Sprite** blocks = new sf::Sprite*[grid.Size];
    for (int i = 0; i < grid.Size; ++i) {
        blocks[i] = new sf::Sprite[grid.Size];
        for (int j = 0; j < grid.Size; ++j) {
            sf::Texture image;
            std::string path = "../external/images/" + std::to_string(grid.Size)
                    + "x" + std::to_string(grid.Size) + "/"
                    + std::to_string(grid.Current_Array[i][j]) + ".png";
            image.loadFromFile(path);
            blocks[i][j].setTexture(image);
            blocks[i][j].setPosition(vx + i * blocksize, vy + j * blocksize);
            window.draw(blocks[i][j]);
        }
    }
}

// Инициализация Пятнашек
int Game(
        int size,
        int blocksize,
        int vx,
        int vy,
        sf::RenderWindow& window,
        sf::Sprite background,
        sf::Font font,
        bool& win)
{
    sf::Event event;
    Grid grid(size);
    grid.Random();
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                // Получаем нажатую клавишу - выполняем соответствующее действие
                if (event.key.code == sf::Keyboard::Escape)
                    return 0;
                if (event.key.code == sf::Keyboard::Left)
                    grid.Left();
                if (event.key.code == sf::Keyboard::Right)
                    grid.Right();
                if (event.key.code == sf::Keyboard::Up)
                    grid.Up();
                if (event.key.code == sf::Keyboard::Down)
                    grid.Down();
            }
            window.draw(background);
            Draw(grid, window, font, blocksize, vx, vy);
            window.display();
        }
        if (grid.CheckWin()) {
            win = true;
            window.draw(background);
            Draw(grid, window, font, blocksize, vx, vy);
            window.display();
            break;
        }
    }
    return grid.Count;
}

void YouWin(sf::RenderWindow& window)
{
    sf::Texture YouWinTexture;
    YouWinTexture.loadFromFile(YOUWIN);
    sf::Sprite YouWin;
    YouWin.setTexture(YouWinTexture);
    YouWin.setScale(2.0f, 2.0f);
    YouWin.setPosition(WIGHT / 2 - 200, 0);
    window.draw(YouWin);
    window.display();
    Sleep(1000);
}

// Вывод Таблицу рекордов из файла
void PrintRecord(sf::RenderWindow& window, sf::Font font)
{
    std::ifstream file("../data/records.txt");
    std::string content;
    bool isRec = true;
    content += "Name Turns Score Date Difficulty\n";
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
