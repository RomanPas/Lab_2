#include <cstdint>
#include <vector>
#include <string>

using vecIt = std::vector<uint32_t>::const_iterator;

std::vector<std::string> split(const std::string& str, const std::string& substr);

std::vector<uint32_t> strIpToVecIp(const std::string& strIp);
uint32_t vecIpToNumber(const std::vector<uint32_t>& vecIp);
std::vector<uint32_t> numberToVecIp(uint32_t ip);
std::string vecIpToStrIp(const std::vector<uint32_t>& vecIp);

std::vector<uint32_t> readData();
std::string getFirstTest(const std::string& line);

std::pair<vecIt, vecIt> findRange(const std::vector<uint32_t>& ips, uint32_t min, uint32_t max);
void inputToVecMinMax(std::vector<uint32_t>& vecMinIp, std::vector<uint32_t>& vecMaxIp, const std::vector<int>& input, size_t id);

void printIp(const uint32_t ip);
void filter(const std::vector<uint32_t>& ips, const int a, const int b = -1, const int c = -1, const int d = -1);
void filterAny(const std::vector<uint32_t>& ips, const uint32_t numb);