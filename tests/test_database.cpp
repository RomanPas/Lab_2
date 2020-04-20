#include "gtest/gtest.h"
#include "tools.h"
#include "ipv4.h"
#include "database.h"

#include <vector>

using namespace std;

namespace {
	class TestDatabase : public Database {
	public:
		const vector<Ipv4>& getData() const;
		pair<itIp, itIp> checkFindRange(Ipv4 min, Ipv4 max);
		bool checkCorrectIp(const std::vector<std::string>& vecStrIp);
	};

	const vector<Ipv4>& TestDatabase::getData() const {
		return data_;
	}

	pair<itIp, itIp> TestDatabase::checkFindRange(Ipv4 min, Ipv4 max) {
		return findRange(min, max);
	}

	bool TestDatabase::checkCorrectIp(const std::vector<std::string>& vecStrIp) {
		return correctIp(vecStrIp);
	}
}

TEST(database, add) {
	TestDatabase database;
	vector<Ipv4> answer = { 0, 77777, 255, 1234, 8 };

	for (auto ip : answer)
		database.addIp(ip);

	auto data = database.getData();
	EXPECT_EQ(data.size(), answer.size());

	for (size_t i = 0; i < answer.size(); ++i)
		EXPECT_EQ(data[i], answer[i]);
}

TEST(database, findRange) {
	TestDatabase database;
	vector<Ipv4> vecIp = { 0, 1, 2, 10, 22, 255, 256, 257, 999 };

	for (auto ip : vecIp)
		database.addIp(ip);

	auto data = database.getData();
	EXPECT_EQ(data.size(), vecIp.size());

	Ipv4 minIp = 0;
	Ipv4 maxIp = 1;
	auto range = database.checkFindRange(minIp, maxIp);
	vector<Ipv4> answer = { 1, 0 };
	vector<Ipv4> result = { range.first, range.second };
	EXPECT_EQ(result.size(), answer.size());
	EXPECT_EQ(result, answer);

	minIp = 0;
	maxIp = 999;
	range = database.checkFindRange(minIp, maxIp);
	answer = { 999, 257, 256, 255, 22, 10, 2, 1, 0 };
	result = { range.first, range.second };
	EXPECT_EQ(result.size(), answer.size());
	EXPECT_EQ(result, answer);

	minIp = 22;
	maxIp = 22;
	range = database.checkFindRange(minIp, maxIp);
	answer = { 22 };
	result = { range.first, range.second };
	EXPECT_EQ(result.size(), answer.size());
	EXPECT_EQ(result, answer);

	minIp = 999;
	maxIp = 1000;
	range = database.checkFindRange(minIp, maxIp);
	answer = { 999 };
	result = { range.first, range.second };
	EXPECT_EQ(result.size(), answer.size());
	EXPECT_EQ(result, answer);

	minIp = 1000;
	maxIp = 999;
	range = database.checkFindRange(minIp, maxIp);
	answer = {};
	result = { range.first, range.second };
	EXPECT_EQ(result.size(), answer.size());
	EXPECT_EQ(result, answer);
}

TEST(database, correctIp) {
	TestDatabase database;

	vector<string> vecStrIp;
	EXPECT_FALSE(database.checkCorrectIp(vecStrIp));

	vecStrIp = { "0" };
	EXPECT_FALSE(database.checkCorrectIp(vecStrIp));

	vecStrIp = { "0", "0", "0", "0", "0" };
	EXPECT_FALSE(database.checkCorrectIp(vecStrIp));

	vecStrIp = { "1", "2", "3", "999" };
	EXPECT_FALSE(database.checkCorrectIp(vecStrIp));

	vecStrIp = { "1", "2", "3", "4" };
	EXPECT_TRUE(database.checkCorrectIp(vecStrIp));

	vecStrIp = { "255", "255", "255", "255" };
	EXPECT_TRUE(database.checkCorrectIp(vecStrIp));

	vecStrIp = { "0", "0", "0", "0" };
	EXPECT_TRUE(database.checkCorrectIp(vecStrIp));
}