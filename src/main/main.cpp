#include <SFML/Graphics.hpp>

#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include <game15_graph.h>
#include <game15_logic.h>

const char* IMAGE
        = "Resource/Pictures/Image.jpg"; // Путь к картинке заднего фона
const char* FONT = "Resource/Font/PakenhamBl_Italic.ttf"; // Путь к шрифту

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
    sf::Text NewGame("New Game", font, 50);
    NewGame.setPosition(100, 200);

    sf::Text TableRecords("Scoreboard", font, 50);
    TableRecords.setPosition(100, 300); // Кнопка "Таблица рекордов"

    sf::Text Exit("Exit", font, 50);
    Exit.setPosition(100, 400); // Кнопка "Выход"

    sf::Text About("About", font, 50);
    About.setPosition(100, 800); // Кнопка "О создателях"

    int diff;
    int count;
    std::string name;
    bool isMenu = 1;
    int menuNum = 0;

    Record NewRecord;
    RecordsTable Table;
    Table.loadTableFromFile();
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
                               100,
                               (WIGHT / 2) - 100 * diff / 2,
                               (HEIGHT / 2) - 100 * diff / 2,
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
            if (menuNum == 2)
                if (DrawRecords(window, background, font))
                    Table.clean();

            if (menuNum == 3) {
                isMenu = false;
            }
            if (menuNum == 4) {
                DrawAbout(window, background, font);
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
