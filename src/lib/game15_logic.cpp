#include <ctime>
#include <fstream>
#include <game15_logic.h>
#include <iostream>
#include <random>
#include <string>

std::string GetCurrentDatetime()
{
    time_t current_time;
    struct tm* timeinfo;
    char buffer[80];

    time(&current_time);
    timeinfo = localtime(&current_time);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    std::string s = buffer;
    return s;
}

Grid::Grid(int size)
{
    for (int i = 0; i < size * size; i++) {
        Win_Array.push_back(i + 1);
        Current_Array.push_back(i + 1);
    }
    Win_Array[size * size - 1] = Current_Array[size * size - 1] = 0;
    Zero_Index = size * size - 1;
    Size = size;
}
bool Grid::CheckWin()
{
    for (int i = 0; i < Size * Size; i++)
        if (Win_Array[i] != Current_Array[i])
            return false;
    return true;
}
void Grid::Random()
{
    srand(time(0));
    int rand;
    do {
        for (int i = 0; i < 10000; i++) {
            rand = (std::rand()) % 4;
            switch (rand) {
            case 0:
                if (!Left())
                    Count--;
                break;
            case 1:
                if (!Right())
                    Count--;
                break;
            case 2:
                if (!Up())
                    Count--;
                break;
            case 3:
                if (!Down())
                    Count--;
                break;
            }
        }
    } while (CheckWin());
}
int Grid::Right()
{
    int temp;
    if (Zero_Index % Size != 0) {
        temp = Current_Array[Zero_Index - 1];
        Current_Array[Zero_Index - 1] = 0;
        Current_Array[Zero_Index] = temp;
        Zero_Index--;
        Count++;
        return 0;
    }
    return 1;
}
int Grid::Left()
{
    int temp;
    if (Zero_Index % Size != Size - 1) {
        temp = Current_Array[Zero_Index + 1];
        Current_Array[Zero_Index + 1] = 0;
        Current_Array[Zero_Index] = temp;
        Zero_Index++;
        Count++;
        return 0;
    }
    return 1;
}
int Grid::Up()
{
    int temp;
    if (Zero_Index < Size * (Size - 1)) {
        temp = Current_Array[Zero_Index + Size];
        Current_Array[Zero_Index + Size] = 0;
        Current_Array[Zero_Index] = temp;
        Zero_Index += Size;
        Count++;
        return 0;
    }
    return 1;
}
int Grid::Down()
{
    int temp;
    if (Zero_Index >= Size) {
        temp = Current_Array[Zero_Index - Size];
        Current_Array[Zero_Index - Size] = 0;
        Current_Array[Zero_Index] = temp;
        Zero_Index -= Size;
        Count++;
        return 0;
    }
    return 1;
}
void ClearFile()
{
    std::ofstream file;
    file.open("Resource/data/records.txt");
    file << "";
    file.close();
}
void RecordsTable::clean()
{
    while (records.size() > 0)
        records.pop_back();
}
void RecordsTable::addRecord(Record record)
{
    records.push_back(record);
    Record temp;
    // Сортируем результаты по счету
    for (int i = 0; i < records.size(); i++)
        for (int j = i + 1; j < records.size(); j++)
            if (records[i].score < records[j].score) {
                temp = records[i];
                records[i] = records[j];
                records[j] = temp;
            }
    // Если количество результатов больше 10 - то удаляем последний
    if (records.size() > 10)
        records.pop_back();
}
// Сохранение таблицы в файле
void RecordsTable::saveTableToFile()
{
    // Открываем или создаем файл "records.txt"
    std::ofstream file;
    file.open("Resource/data/records.txt");
    // Записываем в него все рекорды
    for (int i = 0; i < records.size(); i++) {
        if ((records[i].turns) == "0")
            continue;
        file << records[i].name << "/" << records[i].turns << "/"
             << records[i].score << "/" << records[i].date << "/"
             << records[i].difficly << std::endl;
    }
    // Закрываем файл
    file.close();
}
// Загрузка таблицы из файла
int RecordsTable::loadTableFromFile()
{
    // Открывает файл "records.txt"
    std::ifstream file;
    file.open("Resource/data/records.txt");
    if (!file.is_open())
        return 1;
    // Записывает данные из файла в структуру
    std::string line;
    while (getline(file, line)) {
        Record record;
        size_t pos = 0;
        pos = line.find("/");
        record.name = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find("/");
        record.turns = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find("/");
        record.score = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find("/");
        record.date = line.substr(0, pos);
        line.erase(0, pos + 1);
        record.difficly = line;
        addRecord(record);
    }
    // Закрытие файла
    file.close();
    return 0;
}
