class Grid {
private:
    int** right_index_blocks_;
    int** index_blocks_;
    int Vx_;
    int Vy_;
    int n_;
    int blockSize_;
    sf::Font font_;
    sf::RectangleShape** blocks_;
    sf::Text** texts_;
    sf::Vector2f size_;

public:
    Grid(int n, int blockSize, int Vx, int Vy, sf::Font font);
    ~Grid();
    void Draw(sf::RenderWindow& window);
    void swapBlocks(int x1, int y1, int x2, int y2);
};
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

bool Up(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex);
bool Down(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex);
bool Left(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex);
bool Right(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex);

int Game(
        std::string name,
        int n,
        int blockSize,
        int Vx,
        int Vy,
        int randomaze,
        sf::RenderWindow& window,
        sf::Sprite background,
        sf::Font font);
void PrintRecord(sf::RenderWindow& window, sf::Font font);
void YouWin(sf::RenderWindow& window);

std::string EnterTheName(sf::RenderWindow& window, sf::Sprite background, sf::Font font);
