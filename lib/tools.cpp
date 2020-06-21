#include "tools.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

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