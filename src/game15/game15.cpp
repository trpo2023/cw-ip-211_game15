#include <SFML/Graphics.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <windows.h>

#include "../src/game15_graph/game15_graph.hpp"
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

int main()
{
    RecordsTable Table;
    if (Table.loadTableFromFile())
        return 1;
    sf::Font font;
    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile(IMAGE)) // Загружает текстуру фона
        return 1; // Если текстуры нет, то возвращает ошибку
    sf::Sprite background(backgroundTexture); // Задаем текстуру фону

    background.setScale(1.5f, 1.5f); // Задаем координаты фона
    if (!font.loadFromFile(FONT))    // Загружаем шрифт
        return 1; // Если шрифта нет, то возвращаем ошибку

    sf::RenderWindow window(
            sf::VideoMode(WIGHT, HEIGHT), "Game in 15"); // Инициализация окна

    MainMenu(window, background, font, Table); // Отрисовка главного меню
}
