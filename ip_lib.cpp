#include "ip_lib.h"

#include <iostream>
#include <algorithm>

namespace {
	const size_t MIN_STR_SIZE_IP = 7;	// len(0.0.0.0)
	const size_t MAX_STR_SIZE_IP = 15;	// 255.255.255.255
}

using namespace std;

vector<string> split(const string& str, const string& substr) {
	vector<string> result;
	size_t start = 0;
	size_t stop = str.find_first_of(substr);

	while (stop != string::npos)
	{
		result.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(substr, start);
	}
	result.push_back(str.substr(start));

	return result;
}

vector<uint32_t> strIpToVecIp(const string& strIp) {
	vector<uint32_t> result;
	vector<string> ip = split(strIp, ".");

	if (ip.size() != 4U)
		return {};

	for (const auto& number : ip) {
		if (number.empty() || number.size() > 3U)
			return {};

		if (find_if(number.begin(), number.end(), [](char c) { return !isdigit(c); }) != number.end())
			return {};
	}

	for (size_t i = 0; i < 4U; ++i) {
		result.push_back(stoi(ip[i]));
		if (result[i] > 255U)
			return {};
	}

	return result;
}

uint32_t vecIpToNumber(const vector<uint32_t>& vecIp) {
	uint32_t ip = 0;
	for (size_t i = 0; i < vecIp.size(); ++i) {
		ip <<= 8;
		ip |= vecIp[i];
	}

	return ip;
}

vector<uint32_t> numberToVecIp(uint32_t ip) {
	vector<uint32_t> vecIp = { 0, 0, 0, 0 };
	for (auto it = vecIp.rbegin(); it != vecIp.rend(); ++it) {
		*it = ip & 0xFF;
		ip >>= 8;
	}

	return vecIp;
}

string vecIpToStrIp(const vector<uint32_t>& vecIp) {
	string strIp;
	strIp = to_string(vecIp.front());
	for (size_t i = 1; i < vecIp.size(); ++i) {
		strIp += "." + to_string(vecIp[i]);
	}

	return strIp;
}

vector<uint32_t> readData() {
	vector<uint32_t> ips;

	for (string line; getline(cin, line);)
	{
		string strIp = getFirstTest(line);
		if (strIp == "")
			continue;

		vector<uint32_t> vecIp = strIpToVecIp(strIp);
		if (vecIp.empty())
			continue;

		ips.push_back(vecIpToNumber(vecIp));
	}

	return ips;
}

string getFirstTest(const string& line) {
	if (line.size() < MIN_STR_SIZE_IP + 4U)
		return "";

	size_t pos = line.size() > MAX_STR_SIZE_IP + 4U
		? MAX_STR_SIZE_IP + 1U
		: line.size();

	string::const_iterator start = line.begin();
	string::const_iterator end = start + pos;

	auto it = find_if(start, end, [](const auto& symbol) {return symbol == '\t'; });
	if (it == end)
		return "";

	size_t sizeIp = distance(start, it);
	if (sizeIp < MIN_STR_SIZE_IP)
		return "";

	return line.substr(0, sizeIp);
}

pair<vecIt, vecIt> findRange(const vector<uint32_t>& ips, uint32_t minIp, uint32_t maxIp) {
	if (minIp == maxIp) {
		auto it = lower_bound(ips.rbegin(), ips.rend(), minIp);
		if (it == ips.rend())
			return {};

		return { it.base(), it.base()-- };
	}

	auto rleft = lower_bound(ips.rbegin(), ips.rend(), minIp);
	if (rleft == ips.rend())
		return {};

	auto rright = upper_bound(rleft, ips.rend(), maxIp);
	if (rright == ips.rend())
		rright--;

	return { rright.base()++, rleft.base()-- };
}

void inputToVecMinMax(vector<uint32_t>& vecMinIp, vector<uint32_t>& vecMaxIp, const vector<int>& input, size_t id) {
	if (id == 4U || input[id] < 0 || input[id] > 255)
		return;

	vecMinIp[id] = vecMaxIp[id] = static_cast<unsigned>(input[id]);
	inputToVecMinMax(vecMinIp, vecMaxIp, input, id + 1);
}

void printIp(const uint32_t ip) {

	cout << vecIpToStrIp(numberToVecIp(ip)) << "\n";
}

void filter(const vector<uint32_t>& ips, const int a, const int b, const int c, const int d) {
	if (a < 0 || a > 255)
		return;

	vector<uint32_t> vecMinIp{ 0, 0, 0, 0 };
	vector<uint32_t> vecMaxIp{ 255, 255, 255, 255 };
	inputToVecMinMax(vecMinIp, vecMaxIp, { a, b, c, d }, 0);

	uint32_t minIp = vecIpToNumber(vecMinIp);
	uint32_t maxIp = vecIpToNumber(vecMaxIp);

	auto range = findRange(ips, minIp, maxIp);
	for (auto it = range.first; it != range.second; it++)
		printIp(*it);
}

void filterAny(const vector<uint32_t>& ips, const uint32_t numb) {
	if (numb > 255U)
		return;

	for (uint32_t ip : ips) {
		uint32_t temp = ip;
		for (size_t i = 0; i < 4; ++i) {
			if ((temp & 0xFF) == numb) {
				printIp(ip);
				break;
			}
			temp >>= 8;
		}
	}
}