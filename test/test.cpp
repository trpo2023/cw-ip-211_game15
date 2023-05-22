#include "../thirdparty/ctest.h"

#include <ctime>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

class Grid {
private:
    int** Win_Array;
    int Zero_Index[2];

public:
    int Count = 0;
    int Size;
    int** Current_Array;
    Grid(int size)
    {
        Win_Array = new int*[size];
        Current_Array = new int*[size];
        for (int j = 0; j < size; j++) {
            Win_Array[j] = new int[size];
            Current_Array[j] = new int[size];
            for (int i = 0; i < size; i++) {
                Win_Array[j][i] = j + (size)*i + 1;
                Current_Array[j][i] = j + (size)*i + 1;
            }
        }
        Win_Array[size - 1][size - 1] = Current_Array[size - 1][size - 1] = 0;
        Zero_Index[0] = Zero_Index[1] = size - 1;
        Size = size;
    }
    bool CheckWin()
    {
        for (int i = 0; i < Size; i++)
            for (int j = 0; j < Size; j++)
                if (Win_Array[i][j] != Current_Array[i][j])
                    return false;
        return true;
    }
    void Random()
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
    int Left()
    {
        int temp;
        if (Zero_Index[0] != Size - 1) {
            temp = Current_Array[Zero_Index[0] + 1][Zero_Index[1]];
            Current_Array[Zero_Index[0] + 1][Zero_Index[1]]
                    = Current_Array[Zero_Index[0]][Zero_Index[1]];
            Current_Array[Zero_Index[0]][Zero_Index[1]] = temp;
            Zero_Index[0]++;
            Count++;
            return 0;
        }
        return 1;
    }
    int Right()
    {
        int temp;
        if (Zero_Index[0] != 0) {
            temp = Current_Array[Zero_Index[0] - 1][Zero_Index[1]];
            Current_Array[Zero_Index[0] - 1][Zero_Index[1]]
                    = Current_Array[Zero_Index[0]][Zero_Index[1]];
            Current_Array[Zero_Index[0]][Zero_Index[1]] = temp;
            Zero_Index[0]--;
            Count++;
            return 0;
        }
        return 1;
    }
    int Up()
    {
        int temp;
        if (Zero_Index[1] != Size - 1) {
            temp = Current_Array[Zero_Index[0]][Zero_Index[1] + 1];
            Current_Array[Zero_Index[0]][Zero_Index[1] + 1]
                    = Current_Array[Zero_Index[0]][Zero_Index[1]];
            Current_Array[Zero_Index[0]][Zero_Index[1]] = temp;
            Zero_Index[1]++;
            Count++;
            return 0;
        }
        return 1;
    }
    int Down()
    {
        int temp;
        if (Zero_Index[1] != 0) {
            temp = Current_Array[Zero_Index[0]][Zero_Index[1] - 1];
            Current_Array[Zero_Index[0]][Zero_Index[1] - 1]
                    = Current_Array[Zero_Index[0]][Zero_Index[1]];
            Current_Array[Zero_Index[0]][Zero_Index[1]] = temp;
            Zero_Index[1]--;
            Count++;
            return 0;
        }
        return 1;
    }
};

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