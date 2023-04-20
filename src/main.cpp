#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace sf;
using namespace std;

// ��������� ��� �������� ������ � ������������ � ��� �������
struct Record
{
    string name;
    double money;
    string date;
};

// ��������� ��� �������� ������� ��������
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
    if(isRec)
    {
        // ��������� ������
        window.draw(text);

        // ����������� ���������� �����
        window.display();
        while (!Keyboard::isKeyPressed(Keyboard::Escape));
    }
}

void mainMenu(RenderWindow& window)
{
    // ������� ��� ��� �������� ����
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/img.png"))
    {
        // ��������� ������, ���� �������� �� ������� ���������
    }
    Sprite background(backgroundTexture);

    // ������� ����� ��� ������ �� �������
    Font font;
    if (!font.loadFromFile("images/PakenhamBl_Italic.ttf"))
    {
        // ��������� ������, ���� ����� �� ������� ���������
    }
    background.setPosition(-100, 0);

    // ������� ������ ��� ������
    Text button1("New Game", font, 50);
    button1.setPosition(100, 200); // ��������� ������� ������ ������

    Text button2("Table Records", font, 50);
    button2.setPosition(100, 300); // ��������� ������� ������ ������

    Text button3("Exit", font, 50);
    button3.setPosition(100, 400); // ��������� ������� ������� ������

    Text button4("About", font, 50);
    button4.setPosition(100, 800); // ��������� ������� ��������� ������

    Text about("The Game was created \n by two stogles", font, 50);
    about.setPosition(500, 400);

    bool isMenu = 1;
    int menuNum = 0;

    while (isMenu)
    {
        menuNum = 0;

        window.clear(Color(129, 181, 221));

        if (IntRect(100, 200, 300, 200).contains(Mouse::getPosition(window))) menuNum = 1; 
        if (IntRect(100, 300, 300, 200).contains(Mouse::getPosition(window))) menuNum = 2; 
        if (IntRect(100, 400, 300, 200).contains(Mouse::getPosition(window))) menuNum = 3;
        if (IntRect(100, 800, 300, 200).contains(Mouse::getPosition(window))) menuNum = 4;

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;//���� ������ ������ ������, �� ������� �� ���� 
            if (menuNum == 2) { window.draw(background); print_record(window); window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
            if (menuNum == 3) { window.close(); isMenu = false; }
            if (menuNum == 4) { window.draw(background); window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }

        }

        window.draw(background);
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        window.draw(button4);

        window.display();
    }
    }
int main()
{

    RenderWindow window(sf::VideoMode(1600, 900), "GAME15");
    mainMenu(window);
    RecordsTable recordsTable;

    //// ������ ���������� ����� ������
    //Record rec;
    //int cont = 1;
    //while (cont == 1)
    //{
    //    cout << "Enter yout Nickname";
    //    cin >> rec.name;
    //    cout << endl;
    //    cout << "Enter yout Score";
    //    cin >> rec.money;
    //    cout << endl;
    //    time_t t = time(NULL);
    //    rec.date = __DATE__;
    //    recordsTable.addRecord(rec);
    //    cout << "continue? (1/0)";
    //    cin >> cont;
    //}

    //// ����� ���� ������� �������� �� �����
    //recordsTable.printTable();

    //// ���������� ������� �������� � ����
    //recordsTable.saveTableToFile("records.txt");

    //// �������� ������� �������� �� �����
    //RecordsTable loadedRecordsTable;
    //loadedRecordsTable.loadTableFromFile("records.txt");

    //// ����� ����������� ������� �� �����
    //loadedRecordsTable.printTable();
}