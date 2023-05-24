extern const char* YOUWIN;                     // Путь к текстуре
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
void YouWin(sf::RenderWindow& window);
int Difficulty(sf::RenderWindow& window, sf::Font font, sf::Sprite background);
void DrawRecords(
        sf::RenderWindow& window,
        sf::Sprite background,
        sf::Font font,
        sf::Text about);
int MainMenu(sf::RenderWindow& window, sf::Sprite background, sf::Font font);
void PrintRecord(sf::RenderWindow& window, sf::Font font);
std::string
EnterTheName(sf::RenderWindow& window, sf::Sprite background, sf::Font font);
