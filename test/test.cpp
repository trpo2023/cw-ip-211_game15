#include <ctime>

#include <fstream>

#include <math.h>

#include <stdlib.h>

#include <string.h>

#include "../src/game15_logic/game15_logic.h"

#include "../thirdparty/ctest.h"

CTEST(GridTestSuite, DefaultConstructorTest)
{
    Grid grid(3);

    ASSERT_EQUAL(grid.Size, 3);
    ASSERT_TRUE(grid.CheckWin());
}

CTEST(GridTestSuite, LeftTest)
{
    Grid grid(3);
    // Проверяем, что начальное положение ячеек находится в выигрышной позиции
    ASSERT_TRUE(grid.CheckWin());
    // Делаем несколько ходов влево
    grid.Left();
    grid.Left();
    grid.Left();
    grid.Left();
    // Проверяем, что невозможно сделать ход влево, когда 0-я ячейка находится
    // на крайней левой позиции
    ASSERT_EQUAL(grid.Left(), 1);
}

CTEST(GridTestSuite, RightTest)
{
    Grid grid(3);
    // Проверяем, что начальное положение ячеек находится в выигрышной позиции
    ASSERT_TRUE(grid.CheckWin());
    // Делаем несколько ходов вправо
    grid.Right();
    grid.Right();
    grid.Right();
    // Проверяем, что невозможно сделать ход вправо, когда 0-я ячейка находится
    // на крайней правой позиции
    ASSERT_EQUAL(grid.Right(), 1);
}

CTEST(GridTestSuite, UpTest)
{
    Grid grid(3);
    // Проверяем, что начальное положение ячеек находится в выигрышной позиции
    ASSERT_TRUE(grid.CheckWin());
    // Делаем несколько ходов вверх
    grid.Up();
    grid.Up();
    grid.Up();
    // Проверяем, что невозможно сделать ход вверх, когда 0-я ячейка находится
    // на крайней верхней позиции
    ASSERT_EQUAL(grid.Up(), 1);
}

CTEST(GridTestSuite, DownTest)
{
    Grid grid(3);
    // Проверяем, что начальное положение ячеек находится в выигрышной позиции
    ASSERT_TRUE(grid.CheckWin());
    // Делаем несколько ходов вниз
    grid.Down();
    grid.Down();
    grid.Down();
    // Проверяем, что невозможно сделать ход вниз, когда 0-я ячейка находится на
    // крайней нижней позиции
    ASSERT_EQUAL(grid.Down(), 1);
}

CTEST(RecordsTableTest, AddRecordTest)
{
    RecordsTable table;
    Record record1 = {"John", "5", "1000", "2022-10-31", "hard"};
    table.addRecord(record1);
    ASSERT_EQUAL(table.loadTableFromFile(), 0);
}

CTEST(RecordsTableTest, SaveTableToFileTest)
{
    RecordsTable table;
    Record record1 = {"John", "5", "1000", "2022-10-31", "hard"};
    table.addRecord(record1);
    ASSERT_EQUAL(table.loadTableFromFile(), 0);
    table.saveTableToFile();
    ASSERT_EQUAL(table.loadTableFromFile(), 0);
}

CTEST(RecordsTableTest, LoadTableFromFileTest)
{
    RecordsTable table;
    Record record1 = {"John", "5", "1000", "2022-10-31", "hard"};
    Record record2 = {"Anna", "7", "800", "2022-11-01", "medium"};
    table.addRecord(record1);
    table.addRecord(record2);
    ASSERT_EQUAL(table.loadTableFromFile(), 0);
}

CTEST(GetCurrentDatetimeTest, TestResultLength)
{
    std::string result = GetCurrentDatetime();
    ASSERT_EQUAL(result.length(), 19);
}

CTEST(GetCurrentDatetimeTest, TestStringFormat)
{
    std::string result = GetCurrentDatetime();
    ASSERT_EQUAL(result[4], '-');
    ASSERT_EQUAL(result[7], '-');
    ASSERT_EQUAL(result[10], ' ');
    ASSERT_EQUAL(result[13], ':');
    ASSERT_EQUAL(result[16], ':');
}