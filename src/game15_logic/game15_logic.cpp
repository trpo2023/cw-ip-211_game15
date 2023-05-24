#include "../game15_logic/game15_logic.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <windows.h>

// "Ты Выиграл!"

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

void RecordsTable::addRecord(Record record)
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
void RecordsTable::saveTableToFile()
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
int RecordsTable::loadTableFromFile()
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
