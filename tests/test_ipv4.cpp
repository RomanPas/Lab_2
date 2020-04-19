#include "gtest/gtest.h"
#include "ipv4.h"

#include <string>
#include <vector>

using namespace std;

TEST(ipv4, toString) {
	Ipv4 ip = 0;
	string answer = "0.0.0.0";
	EXPECT_EQ(ip.toString(), answer);

	ip = 1;
	answer = "0.0.0.1";
	EXPECT_EQ(ip.toString(), answer);

	ip = 255;
	answer = "0.0.0.255";
	EXPECT_EQ(ip.toString(), answer);

	ip = 256;
	answer = "0.0.1.0";
	EXPECT_EQ(ip.toString(), answer);

	ip = 65535;
	answer = "0.0.255.255";
	EXPECT_EQ(ip.toString(), answer);

	ip = 65536;
	answer = "0.1.0.0";
	EXPECT_EQ(ip.toString(), answer);

	ip = 16777215;
	answer = "0.255.255.255";
	EXPECT_EQ(ip.toString(), answer);

	ip = 16777216;
	answer = "1.0.0.0";
	EXPECT_EQ(ip.toString(), answer);

	ip = 4294967295;
	answer = "255.255.255.255";
	EXPECT_EQ(ip.toString(), answer);
}

TEST(ipv4, vecIpToIpv4) {
	vector<uint32_t> vecIp = {0, 0, 0, 0};
	Ipv4 answer = 0;
	EXPECT_EQ(vecIpToIpv4(vecIp), answer);

	vecIp = { 0, 0, 0, 1 };
	answer = 1;
	EXPECT_EQ(vecIpToIpv4(vecIp), answer);

	vecIp = { 0, 0, 0, 255 };
	answer = 255;
	EXPECT_EQ(vecIpToIpv4(vecIp), answer);

	vecIp = { 0, 0, 1, 0 };
	answer = 256;
	EXPECT_EQ(vecIpToIpv4(vecIp), answer);

	vecIp = { 0, 0, 255, 255 };
	answer = 65535;
	EXPECT_EQ(vecIpToIpv4(vecIp), answer);

	vecIp = { 0, 1, 0, 0 };
	answer = 65536;
	EXPECT_EQ(vecIpToIpv4(vecIp), answer);

	vecIp = { 1, 0, 0, 0 };
	answer = 16777216;
	EXPECT_EQ(vecIpToIpv4(vecIp), answer);

	vecIp = { 255, 255, 255, 255 };
	answer = 4294967295;
	EXPECT_EQ(vecIpToIpv4(vecIp), answer);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}