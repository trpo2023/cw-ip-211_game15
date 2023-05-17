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

bool Up(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex);
bool Down(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex);
bool Left(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex);
bool Right(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex);
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
        std::string name,
        int n,
        int blockSize,
        int Vx,
        int Vy,
        int randomaze,
        sf::RenderWindow& window,
        sf::Sprite background,
        sf::Font font);
void YouWin(sf::RenderWindow& window);

std::string
EnterTheName(sf::RenderWindow& window, sf::Sprite background, sf::Font font);
