#include "ip_lib.h"
#include <gtest/gtest.h>
#include <string>

int my_argc;
char** my_argv;

using namespace std;

TEST(ip, split) {
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

TEST(ip, getFirstTest) {
	/*
	getFirstTest проверяет сроку и возвращает text1, ограничения :
		*	text1 \t text2 \t text3 (без пробелов)
		*	7 <= len(text1) <= 15
		*	len(line) >= 11
	*/

	string line;
	string answer;

	//	----------------------------------------------------------------
	//	OK

	line = "1.2.3.4\t5\t6";
	answer = "1.2.3.4";
	EXPECT_EQ(getFirstTest(line), answer);

	line = "AAAAAAA\tB\tC";
	answer = "AAAAAAA";
	EXPECT_EQ(getFirstTest(line), answer);

	line = "255.255.255.255\t0\t0";
	answer = "255.255.255.255";
	EXPECT_EQ(getFirstTest(line), answer);

	//	----------------------------------------------------------------
	//	NOT OK

	answer = "";

	line = "";
	EXPECT_EQ(getFirstTest(line), answer);

	line = "123";
	EXPECT_EQ(getFirstTest(line), answer);

	line = "12345678";
	EXPECT_EQ(getFirstTest(line), answer);

	line = "1.2.3.4";
	EXPECT_EQ(getFirstTest(line), answer);

	line = "1.2.3.4 5 6";
	EXPECT_EQ(getFirstTest(line), answer);

	line = "A\tB\tC";
	EXPECT_EQ(getFirstTest(line), answer);

	line = "abcd.255.255.255\t0\t0";
	EXPECT_EQ(getFirstTest(line), answer);

	line = "\t8.8.8.8\t8";
	EXPECT_EQ(getFirstTest(line), answer);

	line = "\t\t8.8.8.8";
	EXPECT_EQ(getFirstTest(line), answer);

	line = "8.8.8.8\t\t";
	EXPECT_EQ(getFirstTest(line), answer);
}

TEST(ip, strIpToVecIp) {
	string strIp;
	vector<uint32_t> answer;

	//	----------------------------------------------------------------
	//	OK

	strIp = "0.0.0.0";
	answer = { 0, 0, 0, 0 };
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "1.2.3.4";
	answer = { 1, 2, 3, 4 };
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "255.255.255.255";
	answer = { 255, 255, 255, 255 };
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "0.255.8.77";
	answer = { 0, 255, 8, 77 };
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	//	----------------------------------------------------------------
	//	NOT OK

	answer = {};

	strIp = "";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "1234567";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "1234567890";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "a.b.c.d";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "0.b.2.3";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "1.2.3";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "1.2.3.4.5";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "1 2 3 4";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "1\t2\t3\t4";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "1\n2\n3\n4";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "-1.1.1.1";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "0.0.0.256";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "256.255.256.256";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "8.8.8888.8";
	EXPECT_EQ(strIpToVecIp(strIp), answer);

	strIp = "0.0.0.2S5";
	EXPECT_EQ(strIpToVecIp(strIp), answer);
}

TEST(ip, vecIpToNumber) {
	vector<uint32_t> vecIp;
	uint32_t answer;

	//	----------------------------------------------------------------
	//	OK

	vecIp = { 0, 0, 0, 0 };
	answer = 0;
	EXPECT_EQ(vecIpToNumber(vecIp), answer);

	vecIp = { 0, 0, 0, 1 };
	answer = 1;
	EXPECT_EQ(vecIpToNumber(vecIp), answer);

	vecIp = { 0, 0, 0, 255 };
	answer = 255;
	EXPECT_EQ(vecIpToNumber(vecIp), answer);

	vecIp = { 0, 0, 1, 0 };
	answer = 256;
	EXPECT_EQ(vecIpToNumber(vecIp), answer);

	vecIp = { 1, 1, 1, 1 };
	answer = 16'843'009;
	EXPECT_EQ(vecIpToNumber(vecIp), answer);

	vecIp = { 255, 255, 255, 255 };
	answer = 4'294'967'295;
	EXPECT_EQ(vecIpToNumber(vecIp), answer);
}

TEST(ip, numberToVecIp) {
	uint32_t ip;
	vector<uint32_t> answer;

	//	----------------------------------------------------------------
	//	OK

	ip = 0;
	answer = { 0, 0, 0, 0 };
	EXPECT_EQ(numberToVecIp(ip), answer);

	ip = 1;
	answer = { 0, 0, 0, 1 };
	EXPECT_EQ(numberToVecIp(ip), answer);

	ip = 255;
	answer = { 0, 0, 0, 255 };
	EXPECT_EQ(numberToVecIp(ip), answer);

	ip = 256;
	answer = { 0, 0, 1, 0 };
	EXPECT_EQ(numberToVecIp(ip), answer);

	ip = 16'843'009;
	answer = { 1, 1, 1, 1 };
	EXPECT_EQ(numberToVecIp(ip), answer);

	ip = 4'294'967'295;
	answer = { 255, 255, 255, 255 };
	EXPECT_EQ(numberToVecIp(ip), answer);
}

TEST(ip, vecIpToStrIp) {
	vector<uint32_t> vecIp;
	string answer;

	//	----------------------------------------------------------------
	//	OK

	vecIp = { 0, 0, 0, 0 };
	answer = "0.0.0.0";
	EXPECT_EQ(vecIpToStrIp(vecIp), answer);

	vecIp = { 1, 2, 3, 4 };
	answer = "1.2.3.4";
	EXPECT_EQ(vecIpToStrIp(vecIp), answer);

	vecIp = { 255, 255, 255, 255 };
	answer = "255.255.255.255";
	EXPECT_EQ(vecIpToStrIp(vecIp), answer);

	vecIp = { 0, 255, 8, 77 };
	answer = "0.255.8.77";
	EXPECT_EQ(vecIpToStrIp(vecIp), answer);
}

TEST(ip, inputToVecMinMax) {
	vector<uint32_t> minAnswer;
	vector<uint32_t> maxAnswer;
	vector<uint32_t> vecMinIp;
	vector<uint32_t> vecMaxIp;
	vector<int> input;

	//	----------------------------------------------------------------
	//	OK

	vecMinIp = { 0, 0, 0, 0 };
	vecMaxIp = { 255, 255, 255, 255 };
	input = { 1, 2, -1, -1 };
	minAnswer = { 1, 2, 0, 0 };
	maxAnswer = { 1, 2, 255, 255 };
	inputToVecMinMax(vecMinIp, vecMaxIp, input, 0);
	EXPECT_EQ(vecMinIp, minAnswer);
	EXPECT_EQ(vecMaxIp, maxAnswer);

	vecMinIp = { 0, 0, 0, 0 };
	vecMaxIp = { 255, 255, 255, 255 };
	input = { 8, 8, 8, 8 };
	minAnswer = { 8, 8, 8, 8 };
	maxAnswer = { 8, 8, 8, 8 };
	inputToVecMinMax(vecMinIp, vecMaxIp, input, 0);
	EXPECT_EQ(vecMinIp, minAnswer);
	EXPECT_EQ(vecMaxIp, maxAnswer);

	vecMinIp = { 0, 0, 0, 0 };
	vecMaxIp = { 255, 255, 255, 255 };
	input = { 255, 0, 0, -1 };
	minAnswer = { 255, 0, 0, 0 };
	maxAnswer = { 255, 0, 0, 255 };
	inputToVecMinMax(vecMinIp, vecMaxIp, input, 0);
	EXPECT_EQ(vecMinIp, minAnswer);
	EXPECT_EQ(vecMaxIp, maxAnswer);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	my_argc = argc;
	my_argv = argv;
	return RUN_ALL_TESTS();
}