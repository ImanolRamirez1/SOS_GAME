#include "pch.h"
#include <iostream>

using namespace std;


TEST(Sprint0, test1) {//This test will consist of adding two numbers together and seeing if the sum is correct/
	int sum;
	int total = 10;
	int a = 5;
	int b = 5;

	sum = a + b;

	ASSERT_EQ(total, sum);

	cout << "Test 1 Completed" << endl;
}
TEST(Sprint0, test2) {//This test will consist of varying the subtraction of one number from another.
	int sum;
	int total = 0;
	int a = 5;
	int b = 5;

	sum = a - b;

	ASSERT_EQ(total, sum);

	cout << "Test 1 Completed" << endl;
}




int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}