#include <gtest/gtest.h>

#include "SimplexMethod.h"
#include "stringtoNum.h"

TEST(SIMPLEX, BASIC) {
	MatrixXd MI;
    VectorXd BV(3);   	
    Initialize(MI, "testData.txt");
	BV << 3, 4, 5;
	double ov = SimplexMethod(MI, BV);
    EXPECT_DOUBLE_EQ(ov, -2.5);
    VectorXd x= get_solution(MI, BV);
    EXPECT_EQ(x.size(), 5);
    EXPECT_DOUBLE_EQ(x[0], 0.5);
    EXPECT_DOUBLE_EQ(x[1], 1.0);
    EXPECT_DOUBLE_EQ(x[2], 0.5);
    EXPECT_DOUBLE_EQ(x[3], 0);
    EXPECT_DOUBLE_EQ(x[4], 0);
}

TEST(SIMPLEX, BASIC_2) {
	MatrixXd MI;
    VectorXd BV(3);   	
    Initialize(MI, "testData.txt");
	BV << 1, 2, 3;
	double ov = SimplexMethod(MI, BV);
    EXPECT_DOUBLE_EQ(ov, -2.5);
    VectorXd x= get_solution(MI, BV);
    EXPECT_EQ(x.size(), 5);
    EXPECT_DOUBLE_EQ(x[0], 0.5);
    EXPECT_DOUBLE_EQ(x[1], 1.0);
    EXPECT_DOUBLE_EQ(x[2], 0.5);
    EXPECT_DOUBLE_EQ(x[3], 0);
    EXPECT_DOUBLE_EQ(x[4], 0);
}

// test two stage simplex
TEST(SIMPLEX, BASIC_3) {
	MatrixXd MI;
    VectorXd BV;   	
    Initialize(MI, "testData.txt");
	BV = TwoStageSimplexMethod(MI);
    double ov = -1 * MI(0, MI.cols() - 1);
    EXPECT_DOUBLE_EQ(ov, -2.5);
    VectorXd x= get_solution(MI, BV);
    EXPECT_EQ(x.size(), 5);
    EXPECT_DOUBLE_EQ(x[0], 0.5);
    EXPECT_DOUBLE_EQ(x[1], 1.0);
    EXPECT_DOUBLE_EQ(x[2], 0.5);
    EXPECT_DOUBLE_EQ(x[3], 0);
    EXPECT_DOUBLE_EQ(x[4], 0);
}