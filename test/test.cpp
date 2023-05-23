#include "../src/game15_logic/game15_logic.h"
#include "../thirdparty/ctest.h"

#include <ctime>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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