#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Ipv4 {
public:
	Ipv4(const uint32_t ip);
	std::string toString();

	friend bool operator< (Ipv4 left, Ipv4 right);
	friend bool operator<= (Ipv4 left, Ipv4 right);
	friend bool operator> (Ipv4 left, Ipv4 right);
	friend bool operator>= (Ipv4 left, Ipv4 right);
	friend bool operator== (Ipv4 left, Ipv4 right);
	friend bool operator!= (Ipv4 left, Ipv4 right);

	operator uint32_t() const;
private:
	uint32_t ip_;
};

std::ostream& operator<< (std::ostream& out, Ipv4 ip);
Ipv4 vecIpToIpv4(const std::vector<uint32_t>& vecIp);