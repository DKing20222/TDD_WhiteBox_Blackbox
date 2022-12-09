//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author David Krhovský
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

const int n = 4; //Matrix size

class Matrix1x1 : public ::testing::Test // Matrix()
{
protected:
    Matrix matrix;
    std::vector<std::vector<double>> test1x1 = {{0}};
};

class MatrixNxN : public ::testing::Test //Matrix(row, col)
{
    protected:
        virtual void SetUp() {
            matrix = Matrix(n, n);
            for(int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; j++)
                {
                    testNxN[i][j] = 1;
                    matrix.set(i, j, (i+j));
                }
            }

            /*
            * [0, 1, 2, 3]
            * [1, 2, 3, 4]
            * [2, 3, 4, 5]
            * [3, 4, 5, 6]
            */
        }

        Matrix matrix;
        std::vector<std::vector<double>>testNxN = std::vector<std::vector< double > >(n, std::vector<double>(n, 1));
};

class MatrixOperators : public ::testing::Test
{
protected:
    virtual void SetUp() {
        matrixA = Matrix(n, n);
        for(int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; j++)
            {
                matrixA.set(i, j, (i+j));
            }
        }
        /*
            * [0, 1, 2, 3]
            * [1, 2, 3, 4]
            * [2, 3, 4, 5]
            * [3, 4, 5, 6]
            */

        matrixB = Matrix(n, n);
        int x = 0;
        for(int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                {
                    matrixB.set(i, j, -x);
                }
                else
                {
                    matrixB.set(i, j, x);
                }
                x++;
            }
        }
        /*
        * [ 0,  1,  2,  3]
        * [ 4,  5,  6,  7]
        * [ 8,  9, 10, 11]
        * [12, 13, 14, 15]
        */

    }
    Matrix matrix1x1A;
    Matrix matrix1x1B;
    Matrix matrixA;
    Matrix matrixB;
};

TEST_F(Matrix1x1, Get)
{
    EXPECT_EQ(matrix.get(0,0), 0);

    EXPECT_ANY_THROW(matrix.get(-132465, -987984));
    EXPECT_ANY_THROW(matrix.get(-1,-1));
    EXPECT_ANY_THROW(matrix.get(1,1));
    EXPECT_ANY_THROW(matrix.get(500, 500));
}

TEST_F(Matrix1x1, Set)
{
    EXPECT_TRUE(matrix.set(0, 0, 1));
    EXPECT_TRUE(matrix.set(0, 0, 0));
    EXPECT_TRUE(matrix.set(0, 0, -1));

    EXPECT_FALSE(matrix.set(-1, -1, 0));
    EXPECT_FALSE(matrix.set(0, -1, 0));
    EXPECT_FALSE(matrix.set(-1, 0, 0));
    EXPECT_FALSE(matrix.set(-132465, -987984, 0));

    EXPECT_TRUE(matrix.set(test1x1));

    test1x1 = {{1}, {1}};
    EXPECT_FALSE(matrix.set(test1x1));
}

TEST_F(MatrixNxN, INIT)
{
    EXPECT_ANY_THROW(Matrix(0, 0));
    EXPECT_ANY_THROW(Matrix(0, 1));
    EXPECT_ANY_THROW(Matrix(1, 0));

    EXPECT_NO_THROW(Matrix(1, 1));
    EXPECT_NO_THROW(Matrix(500, 500));
}


TEST_F(MatrixNxN, Get)
{
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= n; y++)
        {
            matrix = Matrix(x, y);
            for(int i = 0; i < x; ++i)
            {
                for (int j = 0; j < y; j++)
                {
                    matrix.set(i, j,  (i+j));
                }
            }
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++)
                {
                    EXPECT_EQ(matrix.get(i, j), (i+j));
                }
            }
        }
    }
}

TEST_F(MatrixNxN, Set)
{
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= n; y++)
        {
            matrix = Matrix(x, y);

            EXPECT_FALSE(matrix.set(x+1, y+1, 0));

            for(int i = 0; i < x; ++i)
            {
                for (int j = 0; j < y; j++)
                {
                    EXPECT_TRUE(matrix.set(i, j,  (i+j)));
                }
            }
        }
    }
    EXPECT_FALSE(matrix.set(-1, -1, 0));

    EXPECT_TRUE(matrix.set(testNxN));

    testNxN = std::vector<std::vector< double > >(n-1, std::vector<double>(n-1, 1));
    EXPECT_FALSE(matrix.set(testNxN));

    testNxN = std::vector<std::vector< double > >(n+1, std::vector<double>(n+1, 1));
    EXPECT_FALSE(matrix.set(testNxN));
}

TEST_F(MatrixOperators, Equal)
{
    EXPECT_TRUE(matrix1x1A == matrix1x1B); //Same size, same values

    EXPECT_FALSE(matrixA == matrixB); //Same size, different values

    EXPECT_ANY_THROW(if (matrix1x1A == matrixA)); //Different size, different values;
}

TEST_F(MatrixOperators, Addition)
{

    Matrix result = Matrix();
    EXPECT_EQ(matrix1x1A + matrix1x1B, result);

    result = Matrix(n,n);
    int x = 0;
    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                result.set(i, j,  (i+j) - x);
            }
            else
            {
                result.set(i, j,  (i+j) + x);
            }
            x++;
        }
    }
    EXPECT_EQ(matrixA + matrixB, result);

    EXPECT_ANY_THROW(matrix1x1A + matrixA);
}

TEST_F(MatrixOperators, MultiplicationWithMatrix)
{
    Matrix result = Matrix();
    EXPECT_EQ(matrix1x1A * matrix1x1B, result);

    result = Matrix(n,n);
    int values[] = {56, 52, 28, -16, 80, 70, 40, -10, 104, 88, 52, -4, 128, 106, 64, 2};
    int x = 0;
    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            result.set(i, j,  values[x]);
            x++;
        }
    }
    EXPECT_EQ(matrixA * matrixB, result);

    EXPECT_ANY_THROW(matrix1x1A * matrixA);
}

TEST_F(MatrixOperators, MultiplicationWithConst)
{
    Matrix result = Matrix();
    EXPECT_EQ(matrix1x1A * 3, result);
    EXPECT_EQ(matrix1x1A * -161646, result);

    result = Matrix(n,n);
    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            result.set(i, j,  4*(i+j));
        }
    }
    EXPECT_EQ(matrixA * 4, result);

    result = Matrix(n,n);
    int x = 0;
    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                result.set(i, j,  687 * (-x));
            }
            else
            {
                result.set(i, j,  687 * x);
            }
            x++;
        }
    }
    EXPECT_EQ(matrixB * 687, result);
}

TEST_F(MatrixOperators, SolveEquation)
{
    std::vector<double> rightSide = {1, 2, 3, 4};
    std::vector<double> result = {0.5, 0, 0.5, 0};
    matrixA.set(1,1,-2);
    matrixA.set(3,3,-6);

    EXPECT_EQ(matrixA.solveEquation(rightSide), result);

    rightSide = {0, 0, 0};
    EXPECT_ANY_THROW(matrixA.solveEquation(rightSide));

    matrixA = Matrix(2,3);
    EXPECT_ANY_THROW(matrixA.solveEquation(rightSide));

    matrixA = Matrix(3,3);
    EXPECT_ANY_THROW(matrixA.solveEquation(rightSide));

    rightSide = {0};
    EXPECT_ANY_THROW(matrix1x1A.solveEquation(rightSide));

}

TEST_F(MatrixOperators, Transpose)
{
    Matrix result = Matrix();
    EXPECT_EQ(matrix1x1A.transpose(), result);

    result = Matrix(n,n);
    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            result.set(i, j,  (i+j));
        }
    }
    EXPECT_EQ(matrixA.transpose(), result);

    result = Matrix(n,n);
    int x = 0;
    for(int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                result.set(j, i,  -x);
            }
            else
            {
                result.set(j, i,  x);
            }
            x++;
        }
    }
    EXPECT_EQ(matrixB.transpose(), result);
}

TEST_F(MatrixOperators, Inverse)
{
    Matrix result = Matrix();

    Matrix matrixInverse = Matrix(2,2);
    for(int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; j++)
        {
            matrixInverse.set(i, j,  (i+j));
        }
    }

    result = Matrix(2,2);
    int valuesA[] = {-2, 1, 1, 0};
    int x = 0;
    for(int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; j++)
        {
            result.set(i, j,  valuesA[x]);
            x++;
        }
    }

    EXPECT_EQ(matrixInverse.inverse(), result);

    matrixInverse = Matrix(3,3);
    int valuesB[] = {-1,1,0,0,-1,0,0,1,-1};
    x = 0;
    for(int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; j++)
        {
            matrixInverse.set(i, j,  valuesB[x]);
            x++;
        }
    }

    result = Matrix(3,3);
    int valuesBresult[] = {-1,-1,0,0,-1,0,0,-1,-1};
    x = 0;
    for(int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; j++)
        {
            result.set(i, j,  valuesBresult[x]);
            x++;
        }
    }

    EXPECT_EQ(matrixInverse.inverse(), result);

    EXPECT_ANY_THROW(matrix1x1A.inverse());
    EXPECT_ANY_THROW(matrixA.inverse());

    matrixInverse = Matrix(2,2);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            matrixInverse.set(i,j,1);
        }
    }
    EXPECT_ANY_THROW(matrixInverse.inverse());

    matrixInverse = Matrix(3,3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrixInverse.set(i,j,1);
        }
    }
    EXPECT_ANY_THROW(matrixInverse.inverse());
}

/*** Konec souboru white_box_tests.cpp ***/
