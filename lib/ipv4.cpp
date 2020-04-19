#include "ipv4.h"

#include <iostream>
#include <algorithm>

using namespace std;

Ipv4::Ipv4(const uint32_t ip) : ip_(ip) {}

string Ipv4::toString() {
	vector<string> vecStr;
	uint32_t temp = ip_;

	for (size_t i = 0; i < 4; ++i) {
		vecStr.push_back(to_string(temp & 0xFF));
		temp >>= 8;
	}

	reverse(begin(vecStr), end(vecStr));

	string strIp = vecStr.front();
	for (size_t i = 1; i < vecStr.size(); ++i) {
		strIp += ".";
		strIp += vecStr[i];
	}

	return strIp;
}

Ipv4::operator uint32_t() const {
	return ip_;
}

bool operator< (Ipv4 left, Ipv4 right) {
	return left.ip_ < right.ip_;
}

bool operator<= (Ipv4 left, Ipv4 right) {
	return left.ip_ <= right.ip_;
}

bool operator> (Ipv4 left, Ipv4 right) {
	return left.ip_ > right.ip_;
}

bool operator>= (Ipv4 left, Ipv4 right) {
	return left.ip_ >= right.ip_;
}

bool operator== (Ipv4 left, Ipv4 right) {
	return left.ip_ == right.ip_;
}

bool operator!= (Ipv4 left, Ipv4 right) {
	return left.ip_ != right.ip_;
}

ostream& operator<< (ostream& out, Ipv4 ip) {
	out << ip.toString();
	return out;
}

Ipv4 vecIpToIpv4(vector<uint32_t>& vecIp) {
	uint32_t ip = 0;

	ip |= vecIp[0];
	for (size_t i = 1; i < vecIp.size(); ++i) {
		ip <<= 8;
		ip |= vecIp[i];
	}

	return { ip };
}