#include "ip_lib.h"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char const* argv[]) {

	vector<uint32_t> ips = readData();
	cout << ips.size() << endl;
	sort(ips.rbegin(), ips.rend());

	for (auto ip : ips) {
		printIp(ip);
	}

	cout << endl;
	filter(ips, 1);
	cout << endl;
	filter(ips, 46, 70);
	cout << endl;
	filterAny(ips, 46);

	return 0;
}