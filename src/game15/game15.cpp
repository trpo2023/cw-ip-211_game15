#include <SFML/Graphics.hpp>

#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <windows.h>

#include "../game15_graph/game15_graph.h"
#include "../game15_logic/game15_logic.h"

const char* IMAGE
        = "../external/images/image.jpg"; // Путь к картинке заднего фона
const char* FONT = "../external/images/PakenhamBl_Italic.ttf"; // Путь к шрифту

int main(int argc, const char** argv)
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
                NewRecord.date = GetCurrentDatetime();
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
}
