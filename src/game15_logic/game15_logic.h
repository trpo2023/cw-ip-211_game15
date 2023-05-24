#include <SFML/Graphics.hpp>

class Record {
public:
    std::string name;  // Имя игрока
    std::string score; // Счет игрока
    std::string turns; // Потраченное количество ходов
    std::string difficly; // Сложность игры
};

class RecordsTable {
private:
    std::vector<Record> records;

public:
    void addRecord(Record record);
    void saveTableToFile();
    int loadTableFromFile();
};
extern int BlockSize;                          // Размер блока
extern int WIGHT;                              // Ширина окна
extern int HEIGHT;                             // Высота окна
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
        sf::Font font,
        bool& win);
