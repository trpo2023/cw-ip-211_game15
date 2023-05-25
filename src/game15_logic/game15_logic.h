#include <string>
#include <vector>

std::string GetCurrentDatetime();

class Grid {
private:
    int** Win_Array;
    int Zero_Index[2];

public:
    int Count = 0;
    int Size;
    int** Current_Array;
    Grid(int size);
    bool CheckWin();
    void Random();
    int Left();
    int Right();
    int Up();
    int Down();
};
class Record {
public:
    std::string name;  // Имя игрока
    std::string score; // Счет игрока
    std::string turns; // Потраченное количество ходов
    std::string difficly; // Сложность игры
    std::string date;     // Время установления рекорда
};

class RecordsTable {
private:
    std::vector<Record> records;

public:
    void addRecord(Record record);
    void saveTableToFile();
    int loadTableFromFile();
};
