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

int Game(
        int size,
        int blocksize,
        int vx,
        int vy,
        sf::RenderWindow& window,
        sf::Sprite background,
        sf::Font font,
        bool& win);
