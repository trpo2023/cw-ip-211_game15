#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <conio.h>

const int WIGTH = 1000;
const int HEIGTH = 1000;



int mainMenu(RenderWindow& window)
{
    // ������� ��� ��� �������� ����
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/img.png"))
        return 1;
    Sprite background(backgroundTexture);

    // ������� ����� ��� ������ �� �������
    Font font;
    if (!font.loadFromFile("images/PakenhamBl_Italic.ttf"))
        return 1;
    background.setPosition(-100, 0);

    // ������� ������ ��� ������
    Text NewGame("New Game", font, 50);
    NewGame.setPosition(100, 200); // ��������� ������� ������ ������

    Text TableRecords("Table Records", font, 50);
    TableRecords.setPosition(100, 300); // ��������� ������� ������ ������

    Text Exit("Exit", font, 50);
    Exit.setPosition(100, 400); // ��������� ������� ������� ������

    Text About("About", font, 50);
    About.setPosition(100, 800); // ��������� ������� ��������� ������

    Text about("The Game was created \n by two stogles", font, 50);
    about.setPosition(500, 400);
    int diff;
    string name;
    bool isMenu = 1;
    int menuNum = 0;

    while (isMenu)
    {
        menuNum = 0;

        window.clear(Color(129, 181, 221));

        if (IntRect(100, 200, 300, 200).contains(Mouse::getPosition(window))) menuNum = 1;//
        if (IntRect(100, 300, 300, 200).contains(Mouse::getPosition(window))) menuNum = 2;//
        if (IntRect(100, 400, 300, 200).contains(Mouse::getPosition(window))) menuNum = 3;//
        if (IntRect(100, 800, 300, 200).contains(Mouse::getPosition(window))) menuNum = 4;//

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) {
                diff = difficulty(window);
                name = EnterTheName(window);
                Game(name, diff, BlockSize, 900 - BlockSize * diff, 450 - BlockSize * diff, 1000, window);
            }
            if (menuNum == 2) { window.draw(background); print_record(window); window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
            if (menuNum == 3) { isMenu = false; }
            if (menuNum == 4) { window.draw(background); window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }

        }

        window.draw(background);
        window.draw(NewGame);
        window.draw(TableRecords);
        window.draw(Exit);
        window.draw(About);

        window.display();
    }
}

class Grid {
public:
    Grid(int n, int blockSize, int Vx, int Vy) : n_(n), blockSize_(blockSize), Vx_(Vx), Vy_(Vy) {
        // Èíèöèàëèçèðóåì ðàçìåðû ïîëÿ
        size_.x = n_ * blockSize_;
        size_.y = n_ * blockSize_;
        // Çàãðóæàåì øðèôò
        font_.loadFromFile("images/PakenhamBl_Italic.ttf");
        // Íóìåðóåì ïëèòêè
        index_blocks_ = new int* [n_];
        rigth_index_blocks_ = new int* [n_];
        for (int i = 0; i < n_; ++i) {
            index_blocks_[i] = new int[n_];
            rigth_index_blocks_[i] = new int[n_];
            for (int j = 0; j < n_; ++j) {
                index_blocks_[i][j] = i + j * n_;
                rigth_index_blocks_[i][j] = i + j * n_;
            }
        }
        // Èíèöèàëèçèðóåì áëîêè ïîëÿ
        blocks_ = new sf::RectangleShape * [n_];
        texts_ = new sf::Text * [n_];
        for (int i = 0; i < n_; ++i) {
            blocks_[i] = new sf::RectangleShape[n_];
            texts_[i] = new sf::Text[n_];
            for (int j = 0; j < n_; ++j) {
                if (index_blocks_[i][j] == 0) {
                    blocks_[i][j].setSize(sf::Vector2f(blockSize_, blockSize_));
                    blocks_[i][j].setOutlineThickness(1.f);
                    blocks_[i][j].setOutlineColor(sf::Color::Black);
                    blocks_[i][j].setFillColor(sf::Color::Black);// Èíèöèàëèçèðóåì íîìåð áëîêà
                    sf::Vector2f pos(i * blockSize_, j * blockSize_);
                    sf::Text text(std::to_string(index_blocks_[i][j]), font_, 70);
                    text.setPosition(Vx_ + pos.x + 2.f, Vy_ + pos.y + 2.f);
                    text.setFillColor(sf::Color::Black);
                    texts_[i][j] = text;
                    continue;
                }
                blocks_[i][j].setSize(sf::Vector2f(blockSize_, blockSize_));
                blocks_[i][j].setOutlineThickness(1.f);
                blocks_[i][j].setOutlineColor(sf::Color::Black);
                blocks_[i][j].setFillColor(sf::Color::White);

                // Èíèöèàëèçèðóåì íîìåð áëîêà
                sf::Vector2f pos(i * blockSize_, j * blockSize_);
                sf::Text text(std::to_string(index_blocks_[i][j]), font_, 70);
                text.setPosition((float)(Vx_ + pos.x + 2.f), (float)(Vy_ + pos.y + 2.f));
                text.setFillColor(sf::Color::Black);
                texts_[i][j] = text;
            }
        }
    }

    ~Grid() {
        for (int i = 0; i < n_; ++i) {
            delete[] blocks_[i];
        }
        delete[] blocks_;
    }

    void Draw(sf::RenderWindow& window) {
        for (int i = 0; i < n_; ++i) {
            for (int j = 0; j < n_; ++j) {
                sf::Vector2f pos(Vx_ + i * blockSize_, Vy_ + j * blockSize_);
                blocks_[i][j].setPosition(pos);
                window.draw(blocks_[i][j]);
                window.draw(texts_[i][j]);
            }
        }
    }

    sf::Vector2f getSize() const {
        return size_;
    }
    void swapBlocks(int x1, int y1, int x2, int y2)
    {
        std::string Text_temp;
        int index_temp;
        sf::RectangleShape temp;
        temp = blocks_[x1][y1];
        blocks_[x1][y1] = blocks_[x2][y2];
        blocks_[x2][y2] = temp;
        index_temp = index_blocks_[x1][y1];
        index_blocks_[x1][y1] = index_blocks_[x2][y2];
        index_blocks_[x2][y2] = index_temp;
        texts_[x1][y1].setString(std::to_string(index_blocks_[x1][y1]));
        texts_[x2][y2].setString(std::to_string(index_blocks_[x2][y2]));
    }
    // Ïðîâåðêà íà ïîáåäó
    bool CheckWin() {
        for (int i = 0; i < n_; i++)
            for (int j = 0; j < n_; j++)
                if (rigth_index_blocks_[i][j] != index_blocks_[i][j])
                    return false;
        return true;
    }
private:
    int** rigth_index_blocks_;
    int** index_blocks_;
    int Vx_;
    int Vy_;
    int n_; // Ðàçìåð ïîëÿ
    int blockSize_; // Ðàçìåð áëîêà
    sf::Font font_; // Øðèôò òåêñòà
    sf::RectangleShape** blocks_; // Áëîêè ïîëÿ
    sf::Text** texts_; // Òåêñò äëÿ îòîáðàæåíèÿ íîìåðîâ áëîêîâ
    sf::Vector2f size_; // Ðàçìåðû ïîëÿ
};

std::string EnterTheName(sf::RenderWindow& window) {
    sf::RectangleShape square;
    square.setFillColor(sf::Color::Black);
    square.setSize(sf::Vector2f(250, 35));
    square.setPosition(745, 400);
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/img.png"))
        return "Error";
    Sprite background(backgroundTexture);
    background.setPosition(-100, 0);
    sf::Font font;
    if (!font.loadFromFile("images/PakenhamBl_Italic.ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
        return "Error";
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(750, 400);

    sf::Text EnterTheName;
    EnterTheName.setFont(font);
    EnterTheName.setString("Enter The Name");
    EnterTheName.setFillColor(sf::Color::White);
    EnterTheName.setPosition(750, 100);

    std::string input;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.key.code == sf::Keyboard::Enter && input.size() > 0) // Enter
                return input;
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128) // check if input is ASCII
                {
                    if (event.text.unicode == '\b' && input.size() > 0) // backspace
                    {
                        input.pop_back();
                    }

                    else if (event.text.unicode != '\b' && input.size() < 20)
                    {
                        input += static_cast<char>(event.text.unicode);
                    }
                    text.setString(input);
                }
            }
        }


        window.draw(background);
        window.draw(square);
        window.draw(text);
        window.draw(EnterTheName);
        window.display();
    }

    return input;
}

int difficulty(sf::RenderWindow& window) {
    return 3;
}


void Up(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex) {
    if (Zeroindex.y != size - 1) {
        grid.swapBlocks(Zeroindex.x, Zeroindex.y, Zeroindex.x, Zeroindex.y + 1);
        Zeroindex.y++;
        count++;
    }
}
void Down(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex) {
    if (Zeroindex.y != 0) {
        grid.swapBlocks(Zeroindex.x, Zeroindex.y, Zeroindex.x, Zeroindex.y - 1);
        Zeroindex.y--;
        count++;
    }
}
void Left(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex) {
    if (Zeroindex.x != size - 1) {
        grid.swapBlocks(Zeroindex.x, Zeroindex.y, Zeroindex.x + 1, Zeroindex.y);
        Zeroindex.x++;
        count++;
    }
}
void Right(Grid& grid, int& count, int size, sf::Vector2f& Zeroindex) {
    if (Zeroindex.x != 0) {
        grid.swapBlocks(Zeroindex.x, Zeroindex.y, Zeroindex.x - 1, Zeroindex.y);
        Zeroindex.x--;
        count++;
    }
}



int Game(string name, int n, int blockSize, int Vx, int Vy, int randomaze, sf::RenderWindow& window)
{
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/img.png"))
        return 1;
    Sprite background(backgroundTexture);
    background.setPosition(-100, 0);
    int rand;
    int count = 0;
    sf::Vector2f ZeroIndex(0, 0);
    char key;
    bool Pressed = false;
    sf::Event event;
    Grid grid(n, blockSize, Vx, Vy);
    for (int i = 0; i < randomaze; i++) {
        rand = (std::rand()) % 4;
        switch (rand) {
        case 0:
            Left(grid, count, n, ZeroIndex);
            break;
        case 1:
            Right(grid, count, n, ZeroIndex);
            break;
        case 2:
            Up(grid, count, n, ZeroIndex);
            break;
        case 3:
            Down(grid, count, n, ZeroIndex);
            break;
        }
    }
    while (window.isOpen())
    {
        if (grid.CheckWin()) {
            sleep(sf::milliseconds(300));
            break;
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                // Получаем нажатую клавишу - выполняем соответствующее действие
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (event.key.code == sf::Keyboard::Left) Left(grid, count, n, ZeroIndex);
                if (event.key.code == sf::Keyboard::Right) Right(grid, count, n, ZeroIndex);
                if (event.key.code == sf::Keyboard::Up) Up(grid, count, n, ZeroIndex);
                if (event.key.code == sf::Keyboard::Down) Down(grid, count, n, ZeroIndex);
            }

        }
        window.draw(background);
        //window.clear();
        grid.Draw(window);
        window.display();
    }
    return count;
}
struct RecordsTable
{
    vector<Record> records;

    // ������� ��� ���������� ����� ������
    void addRecord(Record record)
    {
        records.push_back(record);
    }

    // ������� ��� ������ ���� ������� �������� �� �����
    void printTable()
    {
        for (int i = 0; i < records.size(); i++)
        {
            cout << "Name: " << records[i].name << " Money: " << records[i].money << " Date: " << records[i].date << endl;
        }
    }

    // ������� ��� ���������� ������� �������� � ����
    void saveTableToFile(string fileName)
    {
        ofstream file;
        file.open(fileName);

        for (int i = 0; i < records.size(); i++)
        {
            file << records[i].name << " " << records[i].date << " " << records[i].money << endl;
        }

        file.close();
    }

    // ������� ��� �������� ������� �������� �� �����
    void loadTableFromFile(string fileName)
    {
        ifstream file;
        file.open("records.txt");

        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                Record record;

                // ��������� ������ �� ��������� �������� � ��������� �� � ���������
                size_t pos = 0;
                pos = line.find(" ");
                record.name = line.substr(0, pos);
                line.erase(0, pos + 1);
                pos = line.find(" ");
                record.money = stod(line.substr(0, pos));
                line.erase(0, pos + 1);
                record.date = line;

                addRecord(record);
            }
            file.close();
        }
    }
};

void print_record(RenderWindow& window) {
    // ��������� ���� ��� ������
    ifstream file("records.txt");
    string content;
    Font font;
    bool isRec = true;
    if (!font.loadFromFile("images/PakenhamBl_Italic.ttf"))
    {
        // ��������� ������, ���� ����� �� ������� ���������
    }
    // ���� ���� ������� �������
    if (file.is_open())
    {
        // ��������� ���������� ����� � ������
        string line;
        while (getline(file, line))
        {
            content += line + "\n";
        }
        file.close();
    }

    Text text(content, font, 40);
    text.setPosition(10, 100); // ������� ������

    // �������� ���� ����������
    if (isRec)
    {
        // ��������� ������
        window.draw(text);

        // ����������� ���������� �����
        window.display();
        while (!Keyboard::isKeyPressed(Keyboard::Escape));
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1800, 900), "Game in 15");
    Game(5, 100, 600, 100, window);
}