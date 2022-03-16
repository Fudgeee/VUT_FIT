//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Adrián Matušík <xmatus35@stud.fit.vutbr.cz>
// $Date:       $2022-03-02
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Adrián Matušík
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

class NonEmptyMatrix : public ::testing::Test
{
protected:
    virtual void SetUp() {   
    }

    Matrix matrix;
};

class EmptyMatrix : public ::testing::Test
{
protected:
    Matrix matrix;
};

TEST_F(EmptyMatrix, Init)
{
    ASSERT_NO_THROW(Matrix());
    ASSERT_NO_THROW(Matrix(1, 1));
    ASSERT_NO_THROW(Matrix(30, 30));
    ASSERT_ANY_THROW(Matrix(0, 0));
}

TEST_F(NonEmptyMatrix, Set1)
{
    ASSERT_NO_THROW(Matrix());
    Matrix matrix1(2, 2);
    Matrix matrix2(1, 1);
    ASSERT_TRUE(matrix1.set(0, 0, 2));
    ASSERT_TRUE(matrix1.set(1, 1, 2));
    ASSERT_FALSE(matrix1.set(2, 2, 2));
    ASSERT_TRUE(matrix2.set(0, 0, 2));
}

TEST_F(NonEmptyMatrix, Set2)
{
    Matrix matrix(1, 1); 
    Matrix matrix1(3, 3);
    ASSERT_TRUE(matrix.set(std::vector<std::vector<double > > {{1}}));
    EXPECT_TRUE(matrix1.set(std::vector<std::vector< double > > {{1, 2, 3},{4, 5, 6}, {7, 8, 9}}));
    EXPECT_FALSE(matrix1.set(std::vector<std::vector< double > > {{1, 2, 3},{4}}));
}

TEST_F(NonEmptyMatrix, Get)
{
    Matrix matrix(1, 1); 
    Matrix matrix1(2, 2);
    ASSERT_NO_THROW(matrix.get(0, 0));
    ASSERT_NO_THROW(matrix1.get(0, 0));
    ASSERT_NO_THROW(matrix1.get(1, 1));
    ASSERT_ANY_THROW(matrix1.get(2, 2));
}

TEST_F(NonEmptyMatrix, OperatorEqual)
{
    Matrix matrix(1, 1);
    Matrix matrix1(2, 2);
    Matrix matrix2(2, 2);
    Matrix matrix3(2, 3);
    matrix.set(std::vector<std::vector<double>> {{1}});
    matrix1.set(std::vector<std::vector<double>> {{1, 20},{3, 4}});
    matrix2.set(std::vector<std::vector<double>> {{1, 20},{3, 4}});
    matrix3.set(std::vector<std::vector<double>> {{1, 2},{3, 4},{5, 6}});
    ASSERT_ANY_THROW(matrix.operator==(matrix1));
    ASSERT_TRUE(matrix1.operator==(matrix2));
    matrix2.set(std::vector<std::vector<double>> {{1, 20},{30, 4}});
    ASSERT_FALSE(matrix1.operator==(matrix2));
    ASSERT_ANY_THROW(matrix2.operator==(matrix3));
}

TEST_F(NonEmptyMatrix, OperatorAdd)
{
    Matrix matrix(1, 1);
    Matrix matrix1(2, 2);
    Matrix matrix2(2, 2);
    Matrix matrix3(2, 3);
    matrix.set(std::vector<std::vector<double>> {{1}});
    matrix1.set(std::vector<std::vector<double>> {{1, 2},{3, 4}});
    matrix2.set(std::vector<std::vector<double>> {{1, 2},{3, 4}});
    matrix3.set(std::vector<std::vector<double>> {{1, 2},{3, 4},{5, 6}});
    Matrix matrix4 = matrix1.operator+(matrix2);
    ASSERT_ANY_THROW(matrix.operator+(matrix1));
    ASSERT_EQ(matrix4.get(0, 0), 2);
    ASSERT_ANY_THROW(matrix3.operator+(matrix1));
}

TEST_F(NonEmptyMatrix, OperatorMultiple)
{
    Matrix matrix(1, 1);
    Matrix matrix1(2, 2);
    Matrix matrix2(2, 2);
    Matrix matrix3(2, 3);
    matrix.set(std::vector<std::vector<double>> {{1}});
    matrix1.set(std::vector<std::vector<double>> {{1, 2},{3, 4}});
    matrix2.set(std::vector<std::vector<double>> {{1, 2},{3, 4}});
    matrix3.set(std::vector<std::vector<double>> {{1, 2},{3, 4},{5, 6}});
    Matrix matrix4 = matrix1.operator*(matrix2);
    ASSERT_ANY_THROW(matrix.operator*(matrix1));
    ASSERT_EQ(matrix4.get(0, 0), 7);
    ASSERT_ANY_THROW(matrix3.operator*(matrix1));
}

TEST_F(NonEmptyMatrix, OperatorMultipleByConst)
{
    Matrix matrix(1, 1);
    Matrix matrix1(2, 2);
    matrix.set(std::vector<std::vector<double>> {{1}});
    Matrix matrix2 = matrix.operator*(3);
    matrix1.set(std::vector<std::vector<double>> {{1, 2},{3, 4}});
    Matrix matrix3 = matrix1.operator*(3);
    ASSERT_EQ(matrix2.get(0, 0), 3);
    ASSERT_EQ(matrix3.get(0, 0), 3);
    ASSERT_NE(matrix3.get(1, 1), 3);
}

TEST_F(NonEmptyMatrix, SolveEquation)
{
    Matrix matrix(1, 1);
    Matrix matrix1(2, 2);
    Matrix matrix2(3, 3);
    Matrix matrix3(2, 3);
    Matrix matrix4(3, 3);
    matrix.set(std::vector<std::vector<double>> {{1}});
    std::vector<double> b{1, 2};
    matrix1.set(std::vector<std::vector<double>> {{1, 20},{13, 4}});
    std::vector<double> b1{10, 12};
    matrix2.set(std::vector<std::vector<double>> {{9, 18, 7},{27, 16, 5}, {5, 4, 23}});
    std::vector<double> b2{20, 35, 30};
    matrix3.set(std::vector<std::vector<double>> {{1, 2},{3, 4},{5, 6}});
    matrix4.set(std::vector<std::vector<double>> {{1, 2, 3},{4, 5, 6},{7, 8, 9}});
    std::vector<double> b3{1, 2, 3};
    ASSERT_ANY_THROW(matrix.solveEquation(b));
    ASSERT_NO_THROW(matrix1.solveEquation(b1));
    ASSERT_NO_THROW(matrix2.solveEquation(b2));
    ASSERT_ANY_THROW(matrix1.solveEquation(b2));
    ASSERT_ANY_THROW(matrix3.solveEquation(b2));
    ASSERT_ANY_THROW(matrix4.solveEquation(b3));
}

TEST_F(NonEmptyMatrix, Transpose)
{
    Matrix matrix1(1, 1);
    Matrix matrix2(2, 2);
    matrix1.set(std::vector<std::vector<double>> {{1}});
    matrix2.set(std::vector<std::vector<double>> {{1, 2},{3, 4}});
    ASSERT_NO_THROW(matrix1.transpose());
    ASSERT_NO_THROW(matrix2.transpose());
}

TEST_F(NonEmptyMatrix, Inverse)
{
    Matrix matrix1(2, 2);
    Matrix matrix2(3, 3);
    Matrix matrix3(1, 1);
    matrix1.set(std::vector<std::vector<double>> {{1, 2},{3, 4}});
    matrix2.set(std::vector<std::vector<double>> {{9, 18, 7},{27, 16, 5}, {5, 4, 23}});
    matrix3.set(std::vector<std::vector<double>> {{1}});
    ASSERT_NO_THROW(matrix1.inverse());
    ASSERT_NO_THROW(matrix2.inverse());
    ASSERT_ANY_THROW(matrix3.inverse());
}

/*** Konec souboru white_box_tests.cpp ***/
