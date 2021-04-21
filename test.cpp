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
}