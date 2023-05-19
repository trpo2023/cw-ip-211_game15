
int Difficulty(sf::RenderWindow& window, sf::Font font, sf::Sprite background);

void DrawRecords(
        sf::RenderWindow& window,
        sf::Sprite background,
        sf::Font font,
        sf::Text about);

int MainMenu(sf::RenderWindow& window, sf::Sprite background, sf::Font font);
void PrintRecord(sf::RenderWindow& window, sf::Font font);

struct Record {
    std::string name;  // Имя игрока
    std::string score; // Счет игрока
    std::string turns; // Потраченное количество ходов
    std::string difficly; // Сложность игры
};

struct RecordsTable {
    std::vector<Record> records;
    // Метод создания новой записи
    void addRecord(Record record);
    // Сохранение таблицы в файле
    void saveTableToFile();
    // Загрузка таблицы из файла
    int loadTableFromFile();
};