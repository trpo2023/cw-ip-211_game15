#include <SFML/Graphics.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <windows.h>

#include "game15_graph.hpp"
#include "game15_logic.hpp"

int main()
{
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

    MainMenu(window, background, font); // Отрисовка главного меню
}
