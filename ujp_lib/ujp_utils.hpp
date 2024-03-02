#ifndef __UJP__UTILS__
#define __UJP__UTILS__

#include <istream>

namespace ujp {
bool is_digit(char car);
bool is_delimiter(char car);

void omit_delimiters(std::istream &input, char &c);

void insert_nSpaces(std::string &str, int n);
} // namespace ujp

#endif