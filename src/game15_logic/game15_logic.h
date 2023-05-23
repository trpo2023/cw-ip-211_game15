#include <SFML/Graphics.hpp>

class Grid {
private:
    int** Win_Array;
    int Zero_Index[2];

public:
    int Count = 0;
    int Size;
    int** Current_Array;
    Grid(int size);
    bool CheckWin();
    void Random();
    int Left();
    int Right();
    int Up();
    int Down();
};

extern const char* IMAGE; // Путь к картинке заднего фона
extern const char* FONT;  // Путь к шрифту
extern const char* YOUWIN; // Путь к текстуре "Ты Выиграл!"

extern int BlockSize;      // Размер блока
extern int WIGHT;          // Ширина окна
extern int HEIGHT;         // Высота окна

extern int NewGame_Size, NewGame_X, NewGame_Y; // "Новая Игра"
extern int TableRecords_Size, TableRecords_X,
        TableRecords_Y;                     // "Таблица Рекордов"
extern int Exit_Size, Exit_X, Exit_Y;       // "Выход"
extern int About_Size, About_X, About_Y;    // "О Создателях"

extern int Easy_Size, Easy_X, Easy_Y;       // "Легкий"
extern int Normal_Size, Normal_X, Normal_Y; // "Средний"
extern int Hard_Size, Hard_X, Hard_Y;       // "Тяжелый"

extern int Field_Size, Field_X, Field_Y;    // Поле для Ввода
int Game(
        int size,
        int blocksize,
        int vx,
        int vy,
        sf::RenderWindow& window,
        sf::Sprite background,
        sf::Font font);
