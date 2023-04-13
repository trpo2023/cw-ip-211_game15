#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <conio.h>

const int WIGTH = 1000;
const int HEIGTH = 1000;



void menu(sf::RenderWindow& window) {

    sf::Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("images/111.png");
    menuTexture2.loadFromFile("images/444.png");
    menuTexture3.loadFromFile("images/333.png");
    menuTexture4.loadFromFile("images/222.png");
    aboutTexture.loadFromFile("images/about.png");
    menuBackground.loadFromFile("images/img.jpg");
    sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menu4(menuTexture4), about(aboutTexture), menuBg(menuBackground);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(100, 30);
    menu2.setPosition(100, 90);
    menu3.setPosition(100, 150);
    menu4.setPosition(100, 600);
    menuBg.setPosition(345, 0);
    while (isMenu)
    {
        menu1.setColor(sf::Color::White);
        menu2.setColor(sf::Color::White);
        menu3.setColor(sf::Color::White);
        menu4.setColor(sf::Color::White);
        menuNum = 0;
        window.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::Blue); menuNum = 1; }
        if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) { menu2.setColor(sf::Color::Blue); menuNum = 2; }
        if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window))) { menu3.setColor(sf::Color::Blue); menuNum = 3; }
        if (sf::IntRect(100, 210, 300, 50).contains(sf::Mouse::getPosition(window))) { menu4.setColor(sf::Color::Blue); menuNum = 4; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;
            if (menuNum == 2) {
                window.draw(menuBg);
                window.display();
                //table_record(); 
                while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
            }
            if (menuNum == 3)
                window.close(); isMenu = false;
            if (menuNum == 4) {
                window.draw(about);
                window.display();
                while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
            }

        }

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);
        window.draw(menu4);
        window.display();
    }
}

class Grid {
public:
    Grid(int n, int blockSize, int Vx, int Vy) : n_(n), blockSize_(blockSize), Vx_(Vx), Vy_(Vy) {
        // Èíèöèàëèçèðóåì ðàçìåðû ïîëÿ
        size_.x = n_ * blockSize_;
        size_.y = n_ * blockSize_;
        // Çàãðóæàåì øðèôò
        font_.loadFromFile("PakenhamBl Italic.ttf");
        // Íóìåðóåì ïëèòêè
        index_blocks_ = new int* [n_];
        rigth_index_blocks_ = new int* [n_];
        for (int i = 0; i < n_; ++i) {
            index_blocks_[i] = new int[n_];
            rigth_index_blocks_[i] = new int[n_];
            for (int j = 0; j < n_; ++j) {
                index_blocks_[i][j] = i + j * n_;
                rigth_index_blocks_[i][j] = i + j * n_;
            }
        }
        // Èíèöèàëèçèðóåì áëîêè ïîëÿ
        blocks_ = new sf::RectangleShape * [n_];
        texts_ = new sf::Text * [n_];
        for (int i = 0; i < n_; ++i) {
            blocks_[i] = new sf::RectangleShape[n_];
            texts_[i] = new sf::Text[n_];
            for (int j = 0; j < n_; ++j) {
                if (index_blocks_[i][j] == 0) {
                    blocks_[i][j].setSize(sf::Vector2f(blockSize_, blockSize_));
                    blocks_[i][j].setOutlineThickness(1.f);
                    blocks_[i][j].setOutlineColor(sf::Color::Black);
                    blocks_[i][j].setFillColor(sf::Color::Black);// Èíèöèàëèçèðóåì íîìåð áëîêà
                    sf::Vector2f pos(i * blockSize_, j * blockSize_);
                    sf::Text text(std::to_string(index_blocks_[i][j]), font_, 70);
                    text.setPosition(Vx_ + pos.x + 2.f, Vy_ + pos.y + 2.f);
                    text.setFillColor(sf::Color::Black);
                    texts_[i][j] = text;
                    continue;
                }
                blocks_[i][j].setSize(sf::Vector2f(blockSize_, blockSize_));
                blocks_[i][j].setOutlineThickness(1.f);
                blocks_[i][j].setOutlineColor(sf::Color::Black);
                blocks_[i][j].setFillColor(sf::Color::White);

                // Èíèöèàëèçèðóåì íîìåð áëîêà
                sf::Vector2f pos(i * blockSize_, j * blockSize_);
                sf::Text text(std::to_string(index_blocks_[i][j]), font_, 70);
                text.setPosition((float)(Vx_ + pos.x + 2.f), (float)(Vy_ + pos.y + 2.f));
                text.setFillColor(sf::Color::Black);
                texts_[i][j] = text;
            }
        }
    }

    ~Grid() {
        for (int i = 0; i < n_; ++i) {
            delete[] blocks_[i];
        }
        delete[] blocks_;
    }

    void Draw(sf::RenderWindow& window) {
        for (int i = 0; i < n_; ++i) {
            for (int j = 0; j < n_; ++j) {
                sf::Vector2f pos(Vx_ + i * blockSize_, Vy_ + j * blockSize_);
                blocks_[i][j].setPosition(pos);
                window.draw(blocks_[i][j]);
                window.draw(texts_[i][j]);
            }
        }
    }

    sf::Vector2f getSize() const {
        return size_;
    }
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
    // Ïðîâåðêà íà ïîáåäó
    bool CheckWin() {
        for (int i = 0; i < n_; i++)
            for (int j = 0; j < n_; j++)
                if (rigth_index_blocks_[i][j] != index_blocks_[i][j])
                    return false;
        return true;
    }
private:
    int** rigth_index_blocks_;
    int** index_blocks_;
    int Vx_;
    int Vy_;
    int n_; // Ðàçìåð ïîëÿ
    int blockSize_; // Ðàçìåð áëîêà
    sf::Font font_; // Øðèôò òåêñòà
    sf::RectangleShape** blocks_; // Áëîêè ïîëÿ
    sf::Text** texts_; // Òåêñò äëÿ îòîáðàæåíèÿ íîìåðîâ áëîêîâ
    sf::Vector2f size_; // Ðàçìåðû ïîëÿ
};

void Up(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex) {
    if (Zeroindex.y != size - 1) {
        grid.swapBlocks(Zeroindex.x, Zeroindex.y, Zeroindex.x, Zeroindex.y + 1);
        Zeroindex.y++;
        count++;
    }
}
void Down(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex) {
    if (Zeroindex.y != 0) {
        grid.swapBlocks(Zeroindex.x, Zeroindex.y, Zeroindex.x, Zeroindex.y - 1);
        Zeroindex.y--;
        count++;
    }
}
void Left(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex) {
    if (Zeroindex.x != size - 1) {
        grid.swapBlocks(Zeroindex.x, Zeroindex.y, Zeroindex.x + 1, Zeroindex.y);
        Zeroindex.x++;
        count++;
    }
}
void Right(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex) {
    if (Zeroindex.x != 0) {
        grid.swapBlocks(Zeroindex.x, Zeroindex.y, Zeroindex.x - 1, Zeroindex.y);
        Zeroindex.x--;
        count++;
    }
}


int Game(int n, int blockSize, int Vx, int Vy, sf::RenderWindow& window)
{
    int count = 0;
    sf::Vector2f ZeroIndex(0, 0);
    char key;
    bool Pressed = false;
    sf::Event event;
    Grid grid(n, blockSize, Vx, Vy);
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                // Получаем нажатую клавишу - выполняем соответствующее действие
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (event.key.code == sf::Keyboard::Left) Left(grid, count, n, ZeroIndex);
                if (event.key.code == sf::Keyboard::Right) Right(grid, count, n, ZeroIndex);
                if (event.key.code == sf::Keyboard::Up) Up(grid, count, n, ZeroIndex);
                if (event.key.code == sf::Keyboard::Down) Down(grid, count, n, ZeroIndex);
            }
        }
        window.clear();
        grid.Draw(window);
        window.display();
    }
    return count;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1800, 900), "Game in 15");
    Game(5, 100, 600, 100, window);
}