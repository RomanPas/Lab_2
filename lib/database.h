#pragma once

#include "ipv4.h"

#include <iostream>
#include <string>
#include <vector>

using itIp = std::vector<Ipv4>::const_iterator;

class Database
{
public:
	Database();
	bool addIp(const std::string& inStrIp);
	bool addIp(const Ipv4 ip);
	void printAllIp();

	template<typename ...Args>
	void filter(Args ... args);
	void filterAny(uint32_t number);

protected:
	std::pair<itIp, itIp> findRange(const Ipv4 minIp, const Ipv4 maxIp);
	bool correctIp(const std::vector<std::string>& vecStrIp);

	std::vector<Ipv4> data_;

private:
	void sortData();

	bool sorted_;
};

template<typename ...Args>
void Database::filter(Args ... args) {
	std::vector<int> data = { args... };
	if (data.size() > 4)
		return;

	if (!sorted_)
		sortData();

	std::vector<uint32_t> minVecIp = { 0, 0, 0, 0 };
	std::vector<uint32_t> maxVecIp = { 255, 255, 255, 255 };

	int index = 0;
	for (auto item : data) {
		minVecIp[index] = item;
		maxVecIp[index] = item;
		++index;
	}

	Ipv4 minIp = vecIpToIpv4(minVecIp);
	Ipv4 maxIp = vecIpToIpv4(maxVecIp);

	auto range = findRange(minIp, maxIp);
	for (auto it = range.first; it != range.second; it++)
		std::cout << *it << "\n";
}
