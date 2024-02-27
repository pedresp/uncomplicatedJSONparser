#ifndef __UJP__UTILS__
#define __UJP__UTILS__

#include <istream>

namespace ujp {
bool is_digit(char car) { return car >= 48 && car <= 58; }
bool is_delimiter(char car) { return car == ' ' || car == '\n' || car == '\t'; }

void omit_delimiters(std::istream &input, char &c) {
  do
    input >> c;
  while (is_delimiter(c) && !input.eof());
}
} // namespace ujp

#endif