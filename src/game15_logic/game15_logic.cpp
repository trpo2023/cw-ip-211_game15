#include <SFML/Graphics.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <windows.h>

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
class Grid {
private:
    int** Win_Array;
    int Zero_Index[2];

public:
    int Count = 0;
    int Size;
    int** Current_Array;
    Grid(int size)
    {
        Win_Array = new int*[size];
        Current_Array = new int*[size];
        for (int j = 0; j < size; j++) {
            Win_Array[j] = new int[size];
            Current_Array[j] = new int[size];
            for (int i = 0; i < size; i++) {
                Win_Array[j][i] = j + (size)*i + 1;
                Current_Array[j][i] = j + (size)*i + 1;
            }
        }
        Win_Array[size - 1][size - 1] = Current_Array[size - 1][size - 1] = 0;
        Zero_Index[0] = Zero_Index[1] = size - 1;
        Size = size;
    }
    bool CheckWin()
    {
        for (int i = 0; i < Size; i++)
            for (int j = 0; j < Size; j++)
                if (Win_Array[i][j] != Current_Array[i][j])
                    return false;
        return true;
    }
    void Random()
    {
        srand(time(0));
        int rand;
        do {
            for (int i = 0; i < 10000; i++) {
                rand = (std::rand()) % 4;
                switch (rand) {
                case 0:
                    if (!Left())
                        Count--;
                    break;
                case 1:
                    if (!Right())
                        Count--;
                    break;
                case 2:
                    if (!Up())
                        Count--;
                    break;
                case 3:
                    if (!Down())
                        Count--;
                    break;
                }
            }
        } while (CheckWin());
    }
    int Left()
    {
        int temp;
        if (Zero_Index[0] != Size - 1) {
            temp = Current_Array[Zero_Index[0] + 1][Zero_Index[1]];
            Current_Array[Zero_Index[0] + 1][Zero_Index[1]]
                    = Current_Array[Zero_Index[0]][Zero_Index[1]];
            Current_Array[Zero_Index[0]][Zero_Index[1]] = temp;
            Zero_Index[0]++;
            Count++;
            return 0;
        }
        return 1;
    }
    int Right()
    {
        int temp;
        if (Zero_Index[0] != 0) {
            temp = Current_Array[Zero_Index[0] - 1][Zero_Index[1]];
            Current_Array[Zero_Index[0] - 1][Zero_Index[1]]
                    = Current_Array[Zero_Index[0]][Zero_Index[1]];
            Current_Array[Zero_Index[0]][Zero_Index[1]] = temp;
            Zero_Index[0]--;
            Count++;
            return 0;
        }
        return 1;
    }
    int Up()
    {
        int temp;
        if (Zero_Index[1] != Size - 1) {
            temp = Current_Array[Zero_Index[0]][Zero_Index[1] + 1];
            Current_Array[Zero_Index[0]][Zero_Index[1] + 1]
                    = Current_Array[Zero_Index[0]][Zero_Index[1]];
            Current_Array[Zero_Index[0]][Zero_Index[1]] = temp;
            Zero_Index[1]++;
            Count++;
            return 0;
        }
        return 1;
    }
    int Down()
    {
        int temp;
        if (Zero_Index[1] != 0) {
            temp = Current_Array[Zero_Index[0]][Zero_Index[1] - 1];
            Current_Array[Zero_Index[0]][Zero_Index[1] - 1]
                    = Current_Array[Zero_Index[0]][Zero_Index[1]];
            Current_Array[Zero_Index[0]][Zero_Index[1]] = temp;
            Zero_Index[1]--;
            Count++;
            return 0;
        }
        return 1;
    }
};
void Draw(
        Grid grid,
        sf::RenderWindow& window,
        sf::Font font,
        int blocksize,
        int vx,
        int vy)
{
    sf::RectangleShape** blocks = new sf::RectangleShape*[grid.Size];
    sf::Text** texts = new sf::Text*[grid.Size];
    for (int i = 0; i < grid.Size; ++i) {
        blocks[i] = new sf::RectangleShape[grid.Size];
        texts[i] = new sf::Text[grid.Size];
        for (int j = 0; j < grid.Size; ++j) {
            blocks[i][j].setSize(sf::Vector2f(blocksize, blocksize));
            blocks[i][j].setOutlineThickness(1.f);
            blocks[i][j].setOutlineColor(sf::Color::Black);
            if (grid.Current_Array[i][j] == 0)
                blocks[i][j].setFillColor(sf::Color::Black);
            else
                blocks[i][j].setFillColor(sf::Color::White);
            sf::Vector2f pos(i * blocksize, j * blocksize);
            texts[i][j].setFont(font);
            texts[i][j].setString(std::to_string(grid.Current_Array[i][j]));
            texts[i][j].setCharacterSize(70);
            texts[i][j].setPosition(
                    (float)(vx + pos.x + 2.f), (float)(vy + pos.y + 2.f));
            texts[i][j].setFillColor(sf::Color::Black);
        }
    }
    for (int i = 0; i < grid.Size; ++i)
        for (int j = 0; j < grid.Size; ++j) {
            sf::Vector2f pos(vx + i * blocksize, vy + j * blocksize);
            blocks[i][j].setPosition(pos);
            window.draw(blocks[i][j]);
            window.draw(texts[i][j]);
        }
}
// Просит игрока ввести имя и возвращает его

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
        if (grid.CheckWin()) {
            win = true;
            break;
        }
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
    }
    return grid.Count;
}
