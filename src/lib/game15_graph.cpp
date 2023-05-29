#include <SFML/Graphics.hpp>

#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <unistd.h>

#include <game15_logic.h>

const char* YOUWIN = "Resource/Pictures/YouWinTexture.jpg"; // Путь к текстуре

int WIGHT = 1800; // Ширина окна
int HEIGHT = 900; // Высота окна

void DrawAbout(sf::RenderWindow& window, sf::Sprite background, sf::Font font)
{
    while ((window.isOpen())) {
        sf::Event event;
        while ((window.pollEvent(event))) {
            if ((event.type == sf::Event::Closed))
                window.close();
            else if ((event.key.code == sf::Keyboard::Escape)) {
                return;
            }
        }
        sf::Text about("The Game was created \n by two stogles", font, 50);
        about.setPosition(500, 400);
        window.draw(background);
        window.draw(about);
        window.display();
    }
}

void Draw(
        Grid grid,
        sf::RenderWindow& window,
        sf::Font font,
        int blocksize,
        int vx,
        int vy)
{
    for (int i = 0; i < grid.Size * grid.Size; ++i) {
        sf::Sprite block;
        sf::Texture image;
        std::string path = "Resource/Pictures/" + std::to_string(grid.Size)
                + "x" + std::to_string(grid.Size) + "/"
                + std::to_string(grid.Current_Array[i]) + ".png";
        image.loadFromFile(path);
        block.setTexture(image);
        block.setPosition(
                vx + (i % grid.Size) * blocksize,
                vy + (i / grid.Size) * blocksize);
        window.draw(block);
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
    sleep(2);
}

// Вывод Таблицу рекордов из файла
void PrintRecord(sf::RenderWindow& window, sf::Font font)
{
    std::ifstream file("Resource/data/records.txt");
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

    window.draw(text);
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
    return 0;
}
// Отрисовывает таблицу рекордов в главном окне
int DrawRecords(sf::RenderWindow& window, sf::Sprite background, sf::Font font)
{
    sf::Text Clear("Clear", font, 40);
    Clear.setFillColor(sf::Color::White);
    Clear.setPosition(0, 700);
    while (window.isOpen()) {
        sf::Event event;
        window.draw(background);
        PrintRecord(window, font);
        window.draw(Clear);
        window.display();
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
                    if (Clear.getGlobalBounds().contains(mousePosition)) {
                        ClearFile();
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
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
