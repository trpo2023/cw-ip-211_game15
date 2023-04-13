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
        