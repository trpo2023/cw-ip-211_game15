
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
