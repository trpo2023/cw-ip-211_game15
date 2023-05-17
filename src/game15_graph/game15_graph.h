int Difficulty(sf::RenderWindow& window, sf::Font font, sf::Sprite background);
struct Record {
    std::string name;
    std::string score;
    std::string turns;
    std::string difficly;
};
struct RecordsTable {
public:
    RecordsTable();
    void addRecord(const Record& record);
    void saveTableToFile() const;
    int loadTableFromFile();
    const std::vector<Record>& getRecords() const;

private:
    std::vector<Record> records;
};
void DrawRecords(
        sf::RenderWindow& window,
        sf::Sprite background,
        sf::Font font,
        sf::Text about);

int MainMenu(sf::RenderWindow& window, sf::Sprite background, sf::Font font);
void PrintRecord(sf::RenderWindow& window, sf::Font font);
