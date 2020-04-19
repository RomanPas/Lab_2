#include "database.h"
#include "ipv4.h"
#include "tools.h"

#include <algorithm>
#include <iostream>

using namespace std;

Database::Database() : sorted_(false) {}

bool Database::addIp(const Ipv4 ip) {
	data_.push_back(ip);
	return true;
}

bool Database::addIp(const std::string& inStrIp) {
	vector<string> vecStrIp = split(inStrIp, ".");

	if (!correctIp(vecStrIp))
		return false;

	uint32_t ip = 0;
	for (const auto& strIp : vecStrIp) {
		ip <<= 8;
		ip |= stoi(strIp);
	}
	data_.emplace_back(ip);

	if (sorted_)
		sorted_ = false;

	return true;
}

void Database::printAllIp() {
	if (!sorted_)
		sortData();

	for (const auto ip : data_)
		cout << ip << "\n";
}

void Database::filterAny(uint32_t number) {
	if (number > 255U)
		return;

	if (!sorted_)
		sortData();

	for (auto ip : data_) {
		uint32_t temp = ip;
		for (size_t i = 0; i < 4; ++i) {
			if ((temp & 0xFF) == number) {
				cout << ip << "\n";
				break;
			}
			temp >>= 8;
		}
	}
}

bool Database::correctIp(const vector<string>& vecStrIp) {
	if (vecStrIp.size() != 4)
		return false;

	uint32_t minStrIp = 0;
	uint32_t maxStrIp = 255;
	for (const auto& strIp : vecStrIp) {
		if (strIp.empty() || strIp.size() > 3U)
			return false;

		if (find_if(begin(strIp), end(strIp), [](char c) { return !isdigit(c); }) != end(strIp))
			return false;

		auto ip = stoi(strIp);
		if (ip < minStrIp || ip > maxStrIp)
			return false;
	}

	return true;
}

void Database::sortData() {
	sort(rbegin(data_), rend(data_));
	sorted_ = true;
}

pair<itIp, itIp> Database::findRange(const Ipv4 minIp, const Ipv4 maxIp) {
	if (minIp > maxIp)
		return {};

	if (!sorted_)
		sortData();

	auto rleft = lower_bound(data_.rbegin(), data_.rend(), minIp);
	if (rleft == data_.rend())
		return {};

	auto rright = upper_bound(rleft, data_.rend(), maxIp);

	return { rright.base(), rleft.base() };
}