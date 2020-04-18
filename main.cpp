#include "ip_lib.h"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char const* argv[]) {

	vector<uint32_t> ips = readData();
	sort(ips.rbegin(), ips.rend());

	for (auto ip : ips) {
		printIp(ip);
	}

	filter(ips, 1);
	filter(ips, 46, 70);
	filterAny(ips, 46);

	return 0;
}