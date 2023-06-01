extern const char* YOUWIN; // Путь к текстуре
extern int WIGHT;          // Ширина окна
extern int HEIGHT;         // Высота окна
void YouWin(sf::RenderWindow& window);
int Difficulty(sf::RenderWindow& window, sf::Font font, sf::Sprite background);
int DrawRecords(sf::RenderWindow& window, sf::Sprite background, sf::Font font);
int MainMenu(sf::RenderWindow& window, sf::Sprite background, sf::Font font);
void PrintRecord(sf::RenderWindow& window, sf::Font font);
std::string
EnterTheName(sf::RenderWindow& window, sf::Sprite background, sf::Font font);
void DrawAbout(sf::RenderWindow& window, sf::Sprite background, sf::Font font);
int Game(
        int size,
        int blocksize,
        int vx,
        int vy,
        sf::RenderWindow& window,
        sf::Sprite background,
        sf::Font font,
        bool& win);