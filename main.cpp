#include "tools.h"
#include "ipv4.h"
#include "database.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main() {
	Database base;

	for (string line; cin >> line;) {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		base.addIp(line);
	}

	base.printAllIp();
	base.filter(1);
	base.filter(46, 70);
	base.filterAny(46);

	return 0;
}