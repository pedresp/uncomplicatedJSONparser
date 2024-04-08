#ifndef __UJP_JSON__
#define __UJP_JSON__

#include <istream>
#include <map>
#include <vector>

#define N_SPACES 4

namespace ujp {
class Scanner;
class JSON;
enum types { UJP_STRING = 1, UJP_NUMBER = 2, UJP_JSON = 3 };
enum parserStates {
  NO_PREV_PARSER = -1,
  CORRECT_PARSER = 0,
  NO_BRACES_CLOSED = 1,
  UNEXPECTED_CHAR = 2,
  UNCOMPLETED_JSON = 3,
  DUPLICATED_KEY = 4,
  EXCESSIVE_RIGHT_BRACES = 5
};

std::ostream &operator<<(std::ostream &co, const JSON &json);

class JSON {

private:
  parserStates parseReturn;
  std::vector<double> numbers;
  std::vector<std::string> strings;
  std::vector<JSON> objects;
  std::map<std::string, std::pair<types, int>> map;
  void to_string(int ident, std::string &str, int count) const;

public:
  JSON();
  JSON(std::istream &stream);

  double getNumber(std::string) const;
  std::string getString(std::string) const;
  JSON &getJSON(std::string);

  bool setNumber(std::string, double);
  bool setString(std::string, std::string);
  bool setJSON(std::string, ujp::JSON &);

  friend Scanner;
  void flush();
  std::string to_string(int ident = N_SPACES) const;
};

std::ostream &operator<<(std::ostream &co, types type);
std::ostream &operator<<(std::ostream &co, parserStates ps);
} // namespace ujp

#endif