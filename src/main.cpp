#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace sf;
using namespace std;

// Структура для хранения данных о пользователе и его рекорде
struct Record {
    string name;
    double money;
    string date;
};

// Структура для хранения таблицы рекордов
struct RecordsTable {
    vector<Record> records;

    // Функция для добавления новой записи
    void addRecord(Record record) {
        records.push_back(record);
    }

    // Функция для вывода всей таблицы рекордов на экран
    void printTable() {
        for (int i = 0; i < records.size(); i++) {
            cout << "Name: " << records[i].name << " Money: " << records[i].money << " Date: " << records[i].date << endl;
        }
    }

    // Функция для сохранения таблицы рекордов в файл
    void saveTableToFile(string fileName) {
        ofstream file;
        file.open(fileName);

        for (int i = 0; i < records.size(); i++) {
            file << records[i].name << " " << records[i].money << " " << records[i].date << endl;
        }

        file.close();
    }

    // Функция для загрузки таблицы рекордов из файла
    void loadTableFromFile(string fileName) {
        ifstream file;
        file.open(fileName);

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                Record record;

                // Разбиваем строку на отдельные значения и сохраняем их в структуру
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

void menu(RenderWindow& window) {

	Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, aboutTexture, menuBackground, escape;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/444.png");
	menuTexture3.loadFromFile("images/333.png");
	menuTexture4.loadFromFile("images/222.png");
	aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("images/img.png");
	escape.loadFromFile("images/esc.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menu4(menuTexture4), about(aboutTexture), menuBg(menuBackground), esc(escape);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menu4.setPosition(100, 600);
	about.setPosition(850, 400);
	menuBg.setPosition(-100, 0);
	esc.setPosition(50, 850);
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menu4.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }
		if (IntRect(100, 600, 300, 50).contains(Mouse::getPosition(window))) { menu4.setColor(Color::Blue); menuNum = 4; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.draw(menuBg); window.display(); window.draw(esc); while (!Keyboard::isKeyPressed(Keyboard::Escape)); ; }
			if (menuNum == 3) { window.close(); isMenu = false; }
			if (menuNum == 4) { window.draw(menuBg); window.draw(about); window.draw(esc); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }

		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);
		window.display();
	}
}
int main() {
    RecordsTable recordsTable;

    // Пример добавления новой записи
    Record rec;
    int cont = 1;
    while (cont == 1)
    {
        cout << "Enter yout Nickname";
        cin >> rec.name;
        cout << endl;
        cout << "Enter yout Score";
        cin >> rec.money;
        cout << endl;
        time_t t = time(NULL);
        rec.date = __DATE__;
        recordsTable.addRecord(rec);
        cout << "continue? (1/0)";
        cin >> cont;
    }

    // Вывод всей таблицы рекордов на экран
    recordsTable.printTable();

    // Сохранение таблицы рекордов в файл
    recordsTable.saveTableToFile("records.txt");

    // Загрузка таблицы рекордов из файла
    RecordsTable loadedRecordsTable;
    loadedRecordsTable.loadTableFromFile("records.txt");

    // Вывод загруженной таблицы на экран
    loadedRecordsTable.printTable();

    return 0;
}