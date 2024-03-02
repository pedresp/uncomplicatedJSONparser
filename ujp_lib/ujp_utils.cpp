#include "ujp_utils.hpp"

namespace ujp {
bool is_digit(char car) { return car >= 48 && car <= 58; }
bool is_delimiter(char car) { return car == ' ' || car == '\n' || car == '\t'; }

void omit_delimiters(std::istream &input, char &c) {
  do
    input >> c;
  while (is_delimiter(c) && !input.eof());
}

void insert_nSpaces(std::string &str, int n) {
  while (n > 0) {
    str.append(" ");
    n--;
  }
}
} // namespace ujp