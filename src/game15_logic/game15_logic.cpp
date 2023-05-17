#include <SFML/Graphics.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <windows.h>

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
class Grid {
private:
    int** right_index_blocks_; // Массив с верным расположением индексов блоков
                               // в сетке
    int** index_blocks_; // Массив с текущим расположением индексов блоков в
                         // сетке
    int Vx_;             // Смещение сетки по X
    int Vy_;             // Смещение сетки по Y
    int n_;              // Количество плиток
    int blockSize_;      // Размер плитки
    sf::Font font_;      // Шрифт
    sf::RectangleShape**
            blocks_; // Массив с текущим расположением плиток в сетке
    sf::Text** texts_; // Массив с текстом для нумерации плиток
    sf::Vector2f size_; // Размеры сетки
public:
    Grid(int n, int blockSize, int Vx, int Vy, sf::Font font)
        : n_(n), blockSize_(blockSize), Vx_(Vx), Vy_(Vy), font_(font)
    {
        // Устанавливаем размеры сетки
        size_.x = size_.y = n_ * blockSize_;
        // Создаем индексные массивы расположени плиток
        index_blocks_ = new int*[n_];
        right_index_blocks_ = new int*[n_];
        for (int i = 0; i < n_; ++i) {
            index_blocks_[i] = new int[n_];
            right_index_blocks_[i] = new int[n_];
            for (int j = 0; j < n_; ++j) {
                index_blocks_[i][j] = i + j * n_;
                right_index_blocks_[i][j] = i + j * n_;
            }
        }
        // создаем сами плитки и их номера
        blocks_ = new sf::RectangleShape*[n_];
        texts_ = new sf::Text*[n_];
        for (int i = 0; i < n_; ++i) {
            blocks_[i] = new sf::RectangleShape[n_];
            texts_[i] = new sf::Text[n_];
            for (int j = 0; j < n_; ++j) {
                if (index_blocks_[i][j] == 0) {
                    blocks_[i][j].setSize(sf::Vector2f(blockSize_, blockSize_));
                    blocks_[i][j].setOutlineThickness(1.f);
                    blocks_[i][j].setOutlineColor(sf::Color::Black);
                    blocks_[i][j].setFillColor(sf::Color::Black);
                    sf::Vector2f pos(i * blockSize_, j * blockSize_);
                    sf::Text text(
                            std::to_string(index_blocks_[i][j]), font_, 70);
                    text.setPosition(Vx_ + pos.x + 2.f, Vy_ + pos.y + 2.f);
                    text.setFillColor(sf::Color::Black);
                    texts_[i][j] = text;
                    continue;
                }
                blocks_[i][j].setSize(sf::Vector2f(blockSize_, blockSize_));
                blocks_[i][j].setOutlineThickness(1.f);
                blocks_[i][j].setOutlineColor(sf::Color::Black);
                blocks_[i][j].setFillColor(sf::Color::White);
                sf::Vector2f pos(i * blockSize_, j * blockSize_);
                sf::Text text(std::to_string(index_blocks_[i][j]), font_, 70);
                text.setPosition(
                        (float)(Vx_ + pos.x + 2.f), (float)(Vy_ + pos.y + 2.f));
                text.setFillColor(sf::Color::Black);
                texts_[i][j] = text;
            }
        }
    }
    ~Grid()
    {
        for (int i = 0; i < n_; ++i) {
            delete[] blocks_[i];
        }
        delete[] blocks_;
    }
    // Функция, отрисовывающая плитки и их номера
    void Draw(sf::RenderWindow& window)
    {
        for (int i = 0; i < n_; ++i) {
            for (int j = 0; j < n_; ++j) {
                sf::Vector2f pos(Vx_ + i * blockSize_, Vy_ + j * blockSize_);
                blocks_[i][j].setPosition(pos);
                window.draw(blocks_[i][j]);
                window.draw(texts_[i][j]);
            }
        }
    }
    // Меняет блоки с выбранными координатами
    void swapBlocks(int x1, int y1, int x2, int y2)
    {
        std::string Text_temp;
        int index_temp;
        sf::RectangleShape temp;
        temp = blocks_[x1][y1];
        blocks_[x1][y1] = blocks_[x2][y2];
        blocks_[x2][y2] = temp;
        index_temp = index_blocks_[x1][y1];
        index_blocks_[x1][y1] = index_blocks_[x2][y2];
        index_blocks_[x2][y2] = index_temp;
        texts_[x1][y1].setString(std::to_string(index_blocks_[x1][y1]));
        texts_[x2][y2].setString(std::to_string(index_blocks_[x2][y2]));
    }
    // Проверка на победу
    bool CheckWin()
    {
        for (int i = 0; i < n_; i++)
            for (int j = 0; j < n_; j++)
                if (right_index_blocks_[i][j] != index_blocks_[i][j])
                    return false;
        return true;
    }
};

// Просит игрока ввести имя и возвращает его
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

// Перемещает тайл с с нижнего мест на пустое
bool Up(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex)
{
    if (Zeroindex.y != size - 1) {
        grid.swapBlocks(Zeroindex.x, Zeroindex.y, Zeroindex.x, Zeroindex.y + 1);
        Zeroindex.y++;
        count++;
        return true;
    }
    return false;
}
// с верхнего
bool Down(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex)
{
    if (Zeroindex.y != 0) {
        grid.swapBlocks(Zeroindex.x, Zeroindex.y, Zeroindex.x, Zeroindex.y - 1);
        Zeroindex.y--;
        count++;
        return true;
    }
    return false;
}
// с правого
bool Left(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex)
{
    if (Zeroindex.x != size - 1) {
        grid.swapBlocks(Zeroindex.x, Zeroindex.y, Zeroindex.x + 1, Zeroindex.y);
        Zeroindex.x++;
        count++;
        return true;
    }
    return false;
}
// с левого
bool Right(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex)
{
    if (Zeroindex.x != 0) {
        grid.swapBlocks(Zeroindex.x, Zeroindex.y, Zeroindex.x - 1, Zeroindex.y);
        Zeroindex.x--;
        count++;
        return true;
    }
    return false;
}
// Инициализация Пятнашек
int Game(
        std::string name,
        int n,
        int blockSize,
        int Vx,
        int Vy,
        int randomaze,
        sf::RenderWindow& window,
        sf::Sprite background,
        sf::Font font)
{
    int rand;
    int count = 0;
    int randcount = 0;
    sf::Vector2f ZeroIndex(0, 0);
    sf::Event event;
    Grid grid(n, blockSize, Vx, Vy, font);
    srand(time(0));
    do {
        for (int i = 0; i < randomaze; i++) {
            rand = (std::rand()) % 4;
            switch (rand) {
            case 0:
                Left(grid, randcount, n, ZeroIndex);
                break;
            case 1:
                Right(grid, randcount, n, ZeroIndex);
                break;
            case 2:
                Up(grid, randcount, n, ZeroIndex);
                break;
            case 3:
                Down(grid, randcount, n, ZeroIndex);
                break;
            }
        }
    } while (grid.CheckWin());
    while (window.isOpen()) {
        if (grid.CheckWin()) {
            YouWin(window);
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
                    Left(grid, count, n, ZeroIndex);
                if (event.key.code == sf::Keyboard::Right)
                    Right(grid, count, n, ZeroIndex);
                if (event.key.code == sf::Keyboard::Up)
                    Up(grid, count, n, ZeroIndex);
                if (event.key.code == sf::Keyboard::Down)
                    Down(grid, count, n, ZeroIndex);
            }
        }
        window.draw(background);
        grid.Draw(window);
        window.display();
    }
    return count;
}