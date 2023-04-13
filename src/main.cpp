#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>

const int WIGTH = 1000;
const int HEIGTH = 1000;

//void table_record() {
//    std::ifstream ifs("leader_board.txt");
//    std::string s;
//    while (ifs)
//    {
//        ifs >> s;
//    }
//    cout << s;
//
//    cin.get();
//}


class Grid {
public:
    Grid(int n, int blockSize) : n_(n), blockSize_(blockSize) {
        // Инициализируем размеры поля
        size_.x = n_ * blockSize_;
        size_.y = n_ * blockSize_;
        // Загружаем шрифт
        font_.loadFromFile("PakenhamBl Italic.ttf");
        // Нумеруем плитки
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
        // Инициализируем блоки поля
        blocks_ = new sf::RectangleShape* [n_];
        texts_ = new sf::Text * [n_];
        for (int i = 0; i < n_; ++i) {
            blocks_[i] = new sf::RectangleShape[n_];
            texts_[i] = new sf::Text[n_];
            for (int j = 0; j < n_; ++j) {
                if (index_blocks_[i][j]==0) {
                    blocks_[i][j].setSize(sf::Vector2f(blockSize_, blockSize_));
                    blocks_[i][j].setOutlineThickness(1.f);
                    blocks_[i][j].setOutlineColor(sf::Color::Black);
                    blocks_[i][j].setFillColor(sf::Color::Black);// Инициализируем номер блока
                    sf::Vector2f pos(i * blockSize_, j * blockSize_);
                    sf::Text text(std::to_string(index_blocks_[i][j]), font_, 70);
                    text.setPosition(pos.x + 2.f, pos.y + 2.f);
                    text.setFillColor(sf::Color::Black);
                    texts_[i][j] = text;
                    continue;
                }
                blocks_[i][j].setSize(sf::Vector2f(blockSize_, blockSize_));
                blocks_[i][j].setOutlineThickness(1.f);
                blocks_[i][j].setOutlineColor(sf::Color::Black);
                blocks_[i][j].setFillColor(sf::Color::White);

                // Инициализируем номер блока
                sf::Vector2f pos(i * blockSize_, j * blockSize_);
                sf::Text text(std::to_string(index_blocks_[i][j]), font_, 70);
                text.setPosition(pos.x + 2.f, pos.y + 2.f);
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
                sf::Vector2f pos(i * blockSize_, j * blockSize_);
                blocks_[i][j].setPosition(pos);
                window.draw(blocks_[i][j]);
                window.draw(texts_[i][j]);
            }
        }
    }
