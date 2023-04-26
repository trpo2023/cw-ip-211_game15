#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <random>

const char* IMAGE = "images/img.png"; // Путь к картинке заднего фона
const char* FONT = "images/PakenhamBl_Italic.ttf"; // Путь к шрифту
int BlockSize = 100; // Размер блока
int WIGHT = 1800; // Ширина окна
int HEIGHT = 900; // Высота окна
int NewGame_Size = 50, NewGame_X = 100, NewGame_Y = 200; // "Новая Игра"
int TableRecords_Size = 50, TableRecords_X = 100, TableRecords_Y = 300; //  "Таблица Рекордов"
int Exit_Size = 50, Exit_X = 100, Exit_Y = 400; // "Выход"
int About_Size = 50, About_X = 100, About_Y = 800; // "О Создателях"
int Easy_Size = 50, Easy_X = 100, Easy_Y = 200; // "Легкий"
int Normal_Size = 50, Normal_X = 100, Normal_Y = 200; // "Средний"
int Hard_Size = 50, Hard_X = 100, Hard_Y = 200; // "Тяжелый"
int Field_Size = 50, Field_X = 100, Field_Y = 200; // Поле для Ввода

struct Record
{
    std::string name;
    std::string money;
    std::string date;
};
struct RecordsTable
{
    std::vector<Record> records;
    // Метод создания новой записи
    void addRecord(Record record)
    {
        records.push_back(record);
    }
    // Сохранение таблицы в файле
    void saveTableToFile() 
    {
        std::ofstream file;
        file.open("records.txt");

        for (int i = 0; i < records.size(); i++)
        {
            file << records[i].name << " " << records[i].date << " " << records[i].money << std::endl;
        }

        file.close();
    }
    // Загрузка таблицы из файла
    void loadTableFromFile()
    {
        std::ifstream file;
        file.open("records.txt");
        if (file.is_open())
        {
            std::string line;
            while (getline(file, line))
            {
                Record record;
                // ��������� ������ �� ��������� �������� � ��������� �� � ���������
                size_t pos = 0;
                pos = line.find(" ");
                record.name = line.substr(0, pos);
                line.erase(0, pos + 1);
                pos = line.find(" ");
                record.money = line.substr(0, pos);
                line.erase(0, pos + 1);
                record.date = line;
                addRecord(record);
            }
            file.close();
        }
    }
};

int MainMenu(sf::RenderWindow& window, sf::Sprite background, sf::Font font, RecordsTable Table)
{
    sf::Text NewGame("New Game", font, NewGame_Size);
    NewGame.setPosition(NewGame_X, NewGame_Y); 

    sf::Text TableRecords("Table Records", font, TableRecords_Size);
    TableRecords.setPosition(TableRecords_X, TableRecords_Y); // Кнопка "Таблица рекордов"

    sf::Text Exit("Exit", font, Exit_Size);
    Exit.setPosition(Exit_X, Exit_Y); // Кнопка "Выход"

    sf::Text About("About", font, About_Size);
    About.setPosition(About_X, About_Y); // Кнопка "О создателях"

    sf::Text about("The Game was created \n by two stogles", font, 50);
        about.setPosition(500, 400);

    int diff;
    int count;
    std::string name;
    bool isMenu = 1;
    int menuNum = 0;
    Record NewRecord;
    

    while (isMenu && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        menuNum = 0;

        window.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(100, 200, 300, 200).contains(sf::Mouse::getPosition(window))) menuNum = 1;//
        if (sf::IntRect(100, 300, 300, 200).contains(sf::Mouse::getPosition(window))) menuNum = 2;//
        if (sf::IntRect(100, 400, 300, 200).contains(sf::Mouse::getPosition(window))) menuNum = 3;//
        if (sf::IntRect(100, 800, 300, 200).contains(sf::Mouse::getPosition(window))) menuNum = 4;//

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) {
                diff = Difficulty(window, font, background);
                if (diff == 0) continue;
                name = EnterTheName(window);
                if (name == "0") continue;
                count = Game(name, diff, BlockSize, WIGHT / 2 - BlockSize * diff, HEIGHT / 2 - BlockSize * diff, 1000, window, background, font);
                NewRecord.name = name;
                NewRecord.money = std::to_string(diff * 1000 - count * 10);
                NewRecord.date = std::to_string(count);
                Table.addRecord(NewRecord);
                Table.saveTableToFile();
            }
            if (menuNum == 2) { DrawRecords(window, background, font, about); }
            if (menuNum == 3) { isMenu = false; }
            if (menuNum == 4) { window.draw(background); window.draw(about); window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }

        }

        window.draw(background);
        window.draw(NewGame);
        window.draw(TableRecords);
        window.draw(Exit);
        window.draw(About);
        window.display();
    }
    return 0;
}


class Grid {
private:
    int** right_index_blocks_;// Массив с верным расположением индексов блоков в сетке
    int** index_blocks_; // Массив с текущим расположением индексов блоков в сетке
    int Vx_; // Смещение сетки по X
    int Vy_; // Смещение сетки по Y
    int n_; // Количество плиток
    int blockSize_; // Размер плитки
    sf::Font font_; // Шрифт
    sf::RectangleShape** blocks_; // Массив с текущим расположением плиток в сетке
    sf::Text** texts_; // Массив с текстом для нумерации плиток
    sf::Vector2f size_; // Размеры сетки
public:
    Grid(int n, int blockSize, int Vx, int Vy,sf::Font font) : n_(n), blockSize_(blockSize), Vx_(Vx), Vy_(Vy),font_(font) {
        // Устанавливаем размеры сетки
        size_.x = size_.y = n_ * blockSize_;
        // Создаем индексные массивы
        index_blocks_ = new int* [n_];
        right_index_blocks_ = new int* [n_];
        for (int i = 0; i < n_; ++i) {
            index_blocks_[i] = new int[n_];
            right_index_blocks_[i] = new int[n_];
            for (int j = 0; j < n_; ++j) {
                index_blocks_[i][j] = i + j * n_;
                right_index_blocks_[i][j] = i + j * n_;
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
                    blocks_[i][j].setFillColor(sf::Color::Black);
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
                if (right_index_blocks_[i][j] != index_blocks_[i][j])
                    return false;
        return true;
    }
};


std::string EnterTheName(sf::RenderWindow& window) {
    sf::RectangleShape Field;
    Field.setFillColor(sf::Color::Black);
    Field.setSize(sf::Vector2f(250, 35));
    Field.setPosition(745,400);
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/img.png"))
        return "Error";
    sf::Sprite background(backgroundTexture);
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
            else if (event.key.code == sf::Keyboard::Escape) return "0";
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
        window.draw(Field);
        window.draw(text);
        window.draw(EnterTheName);
        window.display();
    }

    return input;
}

int Difficulty(sf::RenderWindow& window, sf::Font font, sf::Sprite background) {
    // Создаем шрифт для отображения текста на кнопках
    
    // Создаем кнопки
    sf::Text Easy("Easy", font, 40);
    Easy.setFillColor(sf::Color::White);
    Easy.setPosition(50, 50);

    sf::Text Normal("Normal", font, 40);
    Normal.setFillColor(sf::Color::White);
    Normal.setPosition(50, 150);

    sf::Text Hard("Hard", font, 40);
    Hard.setFillColor(sf::Color::White);
    Hard.setPosition(50, 250);

    // Отображаем кнопки на экране
    window.draw(background);
    window.draw(Easy);
    window.draw(Normal);
    window.draw(Hard);
    window.display();

    // Обрабатываем события до тех пор, пока пользователь не выберет сложность
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.key.code == sf::Keyboard::Escape) return 0;
            else if (event.type == sf::Event::MouseButtonPressed) {
                // Проверяем на какую кнопку нажал пользователь
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (Easy.getGlobalBounds().contains(mousePosition)) {
                        return 3;
                    }
                    else if (Normal.getGlobalBounds().contains(mousePosition)) {
                        return 4;
                    }
                    else if (Hard.getGlobalBounds().contains(mousePosition)) {
                        return 5;
                    }
                }
            }
        }
    }
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

int Game(std::string name, int n, int blockSize, int Vx, int Vy, int randomaze, sf::RenderWindow& window, sf::Sprite background,sf::Font font)
{
    int rand;
    int count = 0;
    int randcount = 0;
    sf::Vector2f ZeroIndex(0, 0);
    char key;
    bool Pressed = false;
    sf::Event event;
    Grid grid(n, blockSize, Vx, Vy,font);
    for (int i = 0; i < randomaze; i++) {
        rand = (std::rand()) % 4;
        switch (rand) {
        case 0:
            Left(grid, randcount, n, ZeroIndex);
            break;
        case 1:
            Right(grid, randcount, n, ZeroIndex);
            break;
        case 2:
            Up(grid, randcount, n, ZeroIndex);
            break;
        case 3:
            Down(grid, randcount, n, ZeroIndex);
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
                if (event.key.code == sf::Keyboard::Escape) return 0;
                if (event.key.code == sf::Keyboard::Left) Left(grid, count, n, ZeroIndex);
                if (event.key.code == sf::Keyboard::Right) Right(grid, count, n, ZeroIndex);
                if (event.key.code == sf::Keyboard::Up) Up(grid, count, n, ZeroIndex);
                if (event.key.code == sf::Keyboard::Down) Down(grid, count, n, ZeroIndex);
            }
            
        }
        window.draw(background);
        grid.Draw(window);
        window.display();
    }
    return count;
}

void PrintRecord(sf::RenderWindow& window,sf::Font font) {
    std::ifstream file("records.txt");
    std::string content;
    bool isRec = true;
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            content += line + "\n";
        }
        file.close();
    }

    sf::Text text(content, font, 40);
    text.setPosition(10, 100); // ������� ������

    // �������� ���� ����������
    if (isRec)
    {
        // ��������� ������
        window.draw(text);

        // ����������� ���������� �����
        window.display();
        while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
    }
}

int main()
{
    RecordsTable Table;
    Table.loadTableFromFile();
    sf::Font font;
    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile(IMAGE)) // Загружает текстуру фона
        return 1; // Если текстуры нет, то возвращает ошибку
    sf::Sprite background(backgroundTexture); // Задаем текстуру фону

    background.setPosition(-100, 0); // Задаем координаты фона
    if (!font.loadFromFile(FONT)) // Загружаем шрифт
        return 1; // Если шрифта нет, то возвращаем ошибку

    sf::RenderWindow window(sf::VideoMode(WIGHT, HEIGHT), "Game in 15"); // Инициализация окна

    MainMenu(window,background,font,Table); // Отрисовка главного меню
}
