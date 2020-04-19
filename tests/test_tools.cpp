#include "gtest/gtest.h"
#include "tools.h"

#include <string>
#include <vector>

using namespace std;

TEST(tools, split) {
	string line;
	vector<string> answer;

	line = "";
	answer = { "" };
	EXPECT_EQ(split(line, "."), answer);

	line = "11";
	answer = { "11" };
	EXPECT_EQ(split(line, "."), answer);

	line = "..";
	answer = { "", "", "" };
	EXPECT_EQ(split(line, "."), answer);

	line = "11.";
	answer = { "11", "" };
	EXPECT_EQ(split(line, "."), answer);

	line = ".11";
	answer = { "", "11" };
	EXPECT_EQ(split(line, "."), answer);

	line = "11.22";
	answer = { "11", "22" };
	EXPECT_EQ(split(line, "."), answer);

	line = "8.8.8.8\t8\t8";
	answer = { "8.8.8.8", "8", "8" };
	EXPECT_EQ(split(line, "\t"), answer);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}